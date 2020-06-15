#ifndef BIDIRECTIONALLIST_H
#define BIDIRECTIONALLIST_H

#include <iostream>
#include <iterator>
#include <memory>
#include <variant>
#include <string>
#include <type_traits>

using ListVariant = std::variant<int, float, std::string>;

class ListItem
{
public:
    virtual std::ostream & print(std::ostream & os) const = 0;

    virtual ~ListItem() = default;

    virtual ListItem * clone() const = 0;

    virtual ListVariant getValue() const = 0;

private:
    ListItem * prev_ = nullptr;
    ListItem * next_ = nullptr;
    friend class BidirectionalList;
};

class IntegerListItem : public ListItem
{
public:
    explicit IntegerListItem(int value);

    virtual ~IntegerListItem() = default;

    virtual std::ostream & print(std::ostream & os) const override;

    virtual IntegerListItem * clone() const override;

    virtual ListVariant getValue() const override;

private:
    int value_;
};

class FloatListItem : public ListItem
{
public:
    explicit FloatListItem(float value);

    virtual ~FloatListItem() = default;

    virtual std::ostream & print(std::ostream & os) const override;

    virtual FloatListItem * clone() const override;

    virtual ListVariant getValue() const override;

private:
    float value_;
};

class StringListItem : public ListItem
{
public:
    explicit StringListItem(const std::string & value);

    virtual ~StringListItem() = default;

    virtual std::ostream & print(std::ostream & os) const override;

    virtual StringListItem * clone() const override;

    virtual ListVariant getValue() const override;

private:
    std::string value_;
};


class BidirectionalList
{
public:

    struct const_iterator
    {        
        const_iterator() = default;

        const_iterator(ListItem * pos, ListItem * last);

        const_iterator & operator++();

        const_iterator operator++(int);

        const_iterator & operator--();

        const_iterator operator--(int);

        bool operator!= (const_iterator other);

        bool operator== (const_iterator other);

        const ListItem * operator *() const;

        const ListItem * operator ->() const;

        ListItem * pos_;
        ListItem * last_;
    };

public:
    // Constructors and destructor
    BidirectionalList() = default;

    BidirectionalList(const BidirectionalList & other);

    BidirectionalList(BidirectionalList && other);

    BidirectionalList & operator= (const BidirectionalList & other);

    BidirectionalList & operator= (BidirectionalList && other);

    ~BidirectionalList();

    // Element access
    const ListItem * front() const;

    const ListItem * back() const;

    // Const iterators
    const_iterator begin() const;

    const_iterator end() const;

    // Size
    bool empty() const;

    std::size_t size() const;

    // Modifiers
    void clear();

    template<class T>
    inline const_iterator insert(const_iterator pos, const T & val);

    const_iterator erase(const_iterator pos);

    template<class T>
    inline void push_back(const T & val);

    void pop_back();

    template<class T>
    inline void push_front(const T & val);

    void pop_front();

    void swap(BidirectionalList & other);

    std::ostream & print(std::ostream & os) const;

private:
    void addFirstItem(ListItem * item);

    void push_back_impl(ListItem * item);

    void push_front_impl(ListItem * item);

    const_iterator insert_impl(ListItem * item, const_iterator pos);

private:
    std::size_t size_ = 0;
    ListItem * first_ = nullptr;
    ListItem * last_  = nullptr;
};

std::ostream & operator << (std::ostream & os, const ListItem * item);
std::ostream & operator << (std::ostream & os, const BidirectionalList & list);


#include <bidirectional_impl.h>


#endif // BIDIRECTIONALLIST_H
