#ifndef BIDIRECTIONAL_IMPL_H
#define BIDIRECTIONAL_IMPL_H

#include "bidirectionallist.h"

template<>
inline void BidirectionalList::push_back(const int & val)
{
    ListItem * item = new IntegerListItem(val);
    push_back_impl(item);
}

template<>
inline void BidirectionalList::push_back(const float & val)
{
    ListItem * item = new FloatListItem(val);
    push_back_impl(item);
}

template<>
inline void BidirectionalList::push_back(const std::string & val)
{
    ListItem * item = new StringListItem(val);
    push_back_impl(item);
}

template<>
inline void BidirectionalList::push_front(const int & val)
{
    ListItem * item = new IntegerListItem(val);
    push_front_impl(item);
}

template<>
inline void BidirectionalList::push_front(const float & val)
{
    ListItem * item = new FloatListItem(val);
    push_front_impl(item);
}

template<>
inline void BidirectionalList::push_front(const std::string & val)
{
    ListItem * item = new StringListItem(val);
    push_front_impl(item);
}

namespace  {
    template<class T>
    inline BidirectionalList::const_iterator insertBoundary(BidirectionalList & list,
                                                            BidirectionalList::const_iterator pos,
                                                            const T & val) {
        BidirectionalList::const_iterator res;
        BidirectionalList::const_iterator itBeg = list.begin();
        BidirectionalList::const_iterator itEnd = list.end();
        if (pos == itBeg) {
            list.push_front(val);
            res = itBeg;
        }
        else if (pos == itEnd) {
            list.push_back(val);
            res = --itEnd;
        }
        return res;
    }
}

template<>
inline BidirectionalList::const_iterator BidirectionalList::insert(BidirectionalList::const_iterator pos, const int & val)
{
    if (pos == begin() || pos == end()) return insertBoundary(*this, pos, val);
    else {
        ListItem * item = new IntegerListItem(val);
        return insert_impl(item, pos);
    }
}

template<>
inline BidirectionalList::const_iterator BidirectionalList::insert(BidirectionalList::const_iterator pos, const float & val)
{
    if (pos == begin() || pos == end()) return insertBoundary(*this, pos, val);
    else {
        ListItem * item = new FloatListItem(val);
        return insert_impl(item, pos);
    }
}

template<>
inline BidirectionalList::const_iterator BidirectionalList::insert(BidirectionalList::const_iterator pos, const std::string & val)
{
    if (pos == begin() || pos == end()) return insertBoundary(*this, pos, val);
    else {
        ListItem * item = new StringListItem(val);
        return insert_impl(item, pos);
    }
}

#endif // BIDIRECTIONAL_IMPL_H
