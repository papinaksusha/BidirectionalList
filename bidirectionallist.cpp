#include "bidirectionallist.h"

#include <iostream>

// ListItem

IntegerListItem::IntegerListItem(int value) : value_(value) {}

void IntegerListItem::print() const { std::cout << value_; }

FloatListItem::FloatListItem(float value) : value_(value) {}

void FloatListItem::print() const { std::cout << value_; }

StringListItem::StringListItem(const std::string & value) : value_(value) {}

void StringListItem::print() const {std::cout << value_; }


// BidirectionalList

BidirectionalList::~BidirectionalList() { clear(); }

void BidirectionalList::clear()
{
    ListItem * tmp;
    for (ListItem * it = first_; it != nullptr; it = tmp) {
        tmp = it->next_;
        delete it;
    }

    for (ListItem * it = first_; it != nullptr; it = tmp) {
        tmp = it->next_;
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

void BidirectionalList::print() const
{
    for (ListItem * it = first_; it != nullptr; it = it->next_) {
        it->print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

void BidirectionalList::addFirstItem(ListItem * item)
{
    first_ = item;
    first_->next_ = item;
    last_ = item;
    last_->prev_ = item;
}
