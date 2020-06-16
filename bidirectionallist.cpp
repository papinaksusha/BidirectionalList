#include "bidirectionallist.h"

#include <iostream>
#include <variant>
#include <type_traits>

// ListItem
IntegerListItem::IntegerListItem(int value)
    : value_(value)
{}

std::ostream & IntegerListItem::print(std::ostream & os) const
{
    return os << value_;
}

IntegerListItem * IntegerListItem::clone() const
{
    return new IntegerListItem(value_);
}

ListVariant IntegerListItem::getValue() const
{
    return value_;
}

FloatListItem::FloatListItem(float value)
    : value_(value)
{}

std::ostream & FloatListItem::print(std::ostream & os) const
{
    return os << value_;
}

FloatListItem * FloatListItem::clone() const
{
    return new FloatListItem(value_);
}

ListVariant FloatListItem::getValue() const
{
    return value_;
}

StringListItem::StringListItem(const std::string & value)
    : value_(value)
{}

StringListItem * StringListItem::clone() const
{
    return new StringListItem(value_);
}

ListVariant StringListItem::getValue() const
{
    return value_;
}

std::ostream & StringListItem::print(std::ostream & os) const
{
    return os << value_;
}


// BidirectionalList
BidirectionalList::BidirectionalList(const BidirectionalList & other)
{
    for (const auto it : other) {
        ListVariant v = it->getValue();
        std::visit([this](auto && arg) {
                   using T = std::decay_t<decltype(arg)>;
                   if constexpr (std::is_same_v<T, int>)
                       this->push_back<int>(arg);
                   else if constexpr (std::is_same_v<T, float>)
                       this->push_back<float>(arg);
                   else if constexpr (std::is_same_v<T, std::string>)
                       this->push_back<std::string>(arg);
               }, v);
    }
}

BidirectionalList::BidirectionalList(BidirectionalList && other)
{
    other.swap(*this);
}

BidirectionalList & BidirectionalList::operator= (const BidirectionalList & other)
{
    BidirectionalList tmp(other);
    tmp.swap(*this);
    return *this;
}

BidirectionalList & BidirectionalList::operator=(BidirectionalList && other)
{
    other.swap(*this);
    return *this;
}

BidirectionalList::~BidirectionalList()
{
    clear();
}

const ListItem * BidirectionalList::front() const
{
    return first_;
}

const ListItem * BidirectionalList::back() const
{
    return last_;
}

BidirectionalList::const_iterator BidirectionalList::begin() const
{
    return const_iterator(first_, last_);
}

BidirectionalList::const_iterator BidirectionalList::end() const
{
    return const_iterator(nullptr, last_);
}

bool BidirectionalList::empty() const
{
    return (size_ == 0);
}

std::size_t BidirectionalList::size() const
{
    return size_;
}

void BidirectionalList::clear()
{
    ListItem * tmp;
    for (ListItem * it = first_; it != nullptr; it = tmp) {
        tmp = it->next_;
        delete it;
        it = nullptr;
    }

    first_ = nullptr;
    last_  = nullptr;
    size_  = 0;
}

BidirectionalList::const_iterator BidirectionalList::erase(BidirectionalList::const_iterator pos)
{
    const_iterator itEnd = end();
    if (empty()) return itEnd;

    const_iterator itBeg = begin();
    if(pos == itBeg) {
        pop_front();
        return begin();
    }

    if(pos == --itEnd) {
        pop_back();
        return end();
    }

    ListItem * it = first_;
    while(it != pos.pos_ && it != nullptr) it = it->next_;

    if (it == nullptr) return itEnd;

    it->prev_->next_ = it->next_;
    it->next_->prev_ = it->prev_;

    const_iterator res(it->next_, last_);
    delete it;
    it = nullptr;
    --size_;
    return res;
}


void BidirectionalList::pop_front()
{
    if (size_ == 1) {
        delete first_;
        first_ = nullptr;
        last_  = nullptr;
    }
    else if (size_ > 1) {
        first_->next_->prev_ = nullptr;
        ListItem * tmp = first_;
        first_ = first_->next_;
        delete tmp;
        tmp = nullptr;
    }
    --size_;
}

void BidirectionalList::pop_back()
{
    if (size_ == 1) {
        delete first_;
        first_ = nullptr;
        last_  = nullptr;
    }
    else if (size_ > 1) {
        last_->prev_->next_ = nullptr;
        ListItem * tmp = last_;
        last_ = last_->prev_;
        delete tmp;
        tmp = nullptr;
    }
    --size_;
}

void BidirectionalList::swap(BidirectionalList & other)
{
    std::swap(first_, other.first_);
    std::swap(last_,  other.last_);
    std::swap(size_,  other.size_);
}

std::ostream &BidirectionalList::print(std::ostream & os) const
{
    for (const auto it : *this) {
        it->print(os);
        os << " ";
    }
    os << std::endl;

    return os;
}

void BidirectionalList::addFirstItem(ListItem * item)
{
    first_ = item;
    last_ = item;
    last_->next_ = nullptr;
}

void BidirectionalList::push_back_impl(ListItem * item)
{
    if (size_ == 0) addFirstItem(item);
    else {
        last_->next_ = item;
        item->prev_ = last_;
        last_ = item;
        last_->next_ = nullptr;
    }

    ++size_;
}

void BidirectionalList::push_front_impl(ListItem * item)
{
    if (size_ == 0) addFirstItem(item);
    else {
        first_->prev_ = item;
        item->next_ = first_;
        first_ = item;
        first_->prev_ = nullptr;
    }

    ++size_;
}

BidirectionalList::const_iterator BidirectionalList::insert_impl(ListItem * item, const_iterator pos)
{
    ListItem * it;
    for (it = first_; it != pos.pos_; it = it->next_);

    it->prev_->next_ = item;
    item->prev_ = it->prev_;
    it->prev_ = item;
    item->next_ = it;
    ++size_;

    return  const_iterator(item, last_);
}

// const_iterator
BidirectionalList::const_iterator::const_iterator(ListItem *pos, ListItem *last)
    : pos_(pos)
    , last_(last)
{}

BidirectionalList::const_iterator & BidirectionalList::const_iterator::operator++()
{
    pos_ = pos_->next_;
    return *this;
}

BidirectionalList::const_iterator BidirectionalList::const_iterator::operator++(int)
{
    const_iterator tmp(*this);
    ++(*this);
    return tmp;
}

BidirectionalList::const_iterator & BidirectionalList::const_iterator::operator--()
{
    if (pos_ == nullptr) pos_ = last_;
    else pos_ = pos_->prev_;
    return *this;
}

BidirectionalList::const_iterator BidirectionalList::const_iterator::operator--(int)
{
    const_iterator tmp(*this);
    --(*this);
    return tmp;
}

bool BidirectionalList::const_iterator::operator!= (BidirectionalList::const_iterator other)
{
    return pos_ != other.pos_;
}

bool BidirectionalList::const_iterator::operator== (BidirectionalList::const_iterator other)
{
    return pos_ == other.pos_;
}

const ListItem *BidirectionalList::const_iterator::operator *() const
{
    return pos_;
}

const ListItem * BidirectionalList::const_iterator::operator ->() const
{
    return pos_;
}


// Output
std::ostream & operator <<(std::ostream & os, const BidirectionalList & list)
{
    return list.print(os);
}

std::ostream & operator <<(std::ostream &os, const ListItem * item)
{
    return item->print(os);
}

