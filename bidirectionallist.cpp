#include "bidirectionallist.h"

#include <iostream>

// ListItem

IntegerListItem::IntegerListItem(int value) : value_(value) {}

std::ostream & IntegerListItem::print(std::ostream & os) const { return os << value_; }

IntegerListItem *IntegerListItem::clone() const { return new IntegerListItem(value_); }

FloatListItem::FloatListItem(float value) : value_(value) {}

std::ostream & FloatListItem::print(std::ostream & os) const { return os << value_; }

FloatListItem * FloatListItem::clone() const { return new FloatListItem(value_); }

StringListItem::StringListItem(const std::string & value) : value_(value) {}

StringListItem * StringListItem::clone() const { return new StringListItem(value_); }

std::ostream & StringListItem::print(std::ostream & os) const { return os << value_; }


// BidirectionalList

BidirectionalList::~BidirectionalList() { clear(); }

// не очень хорошо, лучше через operator= через swap и конструктор, но для краткости
BidirectionalList::BidirectionalList(const BidirectionalList & other)
{
    operator=(other);
}

BidirectionalList::BidirectionalList(BidirectionalList && other)
{
    first_ = other.first_;
    last_  = other.last_;
    other.first_ = nullptr;
    other.last_  = nullptr;
}

BidirectionalList & BidirectionalList::operator= (const BidirectionalList & other)
{
    if (this != &other)
    {
        this->clear();
        first_ = other.first_->clone();
        first_->prev_ = nullptr;
        ListItem * it = first_;

        for (ListItem * othIt = other.first_->next_; othIt != nullptr; othIt = othIt->next_, it = it->next_) {
            it->next_ = othIt->clone();
            it->next_->prev_ = it->next_;
        }

        last_ = it;
    }

    return *this;
}

BidirectionalList &BidirectionalList::operator=(BidirectionalList && other)
{
    clear();

    first_ = other.first_;
    last_  = other.last_;
    other.first_ = nullptr;
    other.last_  = nullptr;

    return *this;
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
}

void BidirectionalList::insert(ListItem * pos, ListItem * item)
{
    if (pos == first_) {
        push_front(item);
    }
    else if (pos == nullptr) {
        push_back(item);
    }
    else {
        ListItem * it;
        for (it = first_; it != pos; it = it->next_);

        it->prev_->next_ = item;
        item->prev_ = it->prev_;                
        it->prev_ = item;
        item->next_ = it;
    }
}

void BidirectionalList::push_back(ListItem * item)
{
    if (first_ == nullptr) addFirstItem(item);

    last_->next_ = item;
    item->prev_ = last_;
    last_ = item;
}

void BidirectionalList::push_front(ListItem * item)
{
    if (first_ == nullptr) addFirstItem(item);

    first_->prev_ = item;
    item->next_ = first_;
    first_ = item;
}

ListItem *BidirectionalList::erase(ListItem * pos)
{
    if (first_ == nullptr) return nullptr;

    if (pos == first_) pop_front();
    else if (pos == last_) pop_back();
    else {
        pos->prev_->next_ = pos->next_;
        pos->next_->prev_ = pos->prev_;
    }

    ListItem * posNext = pos->next_;
    delete pos;
    pos = nullptr;
    return posNext;
}

void BidirectionalList::pop_front()
{
    first_->next_->prev_ = nullptr;
    ListItem * tmp = first_;
    first_ = first_->next_;
    delete tmp;
    tmp = nullptr;
}

void BidirectionalList::pop_back()
{
    last_->prev_->next_ = nullptr;
    ListItem * tmp = last_;
    last_ = last_->prev_;
    delete tmp;
    tmp = nullptr;
}

std::ostream &BidirectionalList::print(std::ostream & os) const
{
    for (ListItem * it = first_; it != nullptr; it = it->next_) {
        it->print(os);
        os << " ";
    }
    os << std::endl;

    return os;
}

void BidirectionalList::addFirstItem(ListItem * item)
{
    first_ = item;
    first_->next_ = item;
    last_ = item;
    last_->prev_ = item;
}

std::ostream & operator <<(std::ostream & os, const BidirectionalList & list)
{
    return list.print(os);
}

std::ostream & operator <<(std::ostream &os, ListItem *item)
{
    return item->print(os);
}
