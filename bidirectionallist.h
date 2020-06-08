#ifndef BIDIRECTIONALLIST_H
#define BIDIRECTIONALLIST_H

#include <string>
#include <iostream>

struct ListItem
{
    virtual std::ostream & print(std::ostream & os) const = 0;
    virtual ~ListItem() = default;
    virtual ListItem * clone() const = 0;

    ListItem* prev_ = nullptr;
    ListItem* next_ = nullptr;
};


struct IntegerListItem : public ListItem
{
    explicit IntegerListItem(int value);
    virtual ~IntegerListItem() = default;
    virtual std::ostream & print(std::ostream & os) const override;
    virtual IntegerListItem * clone() const override;

private:
    int value_;
};

struct FloatListItem : public ListItem
{
    explicit FloatListItem(float value);
    virtual ~FloatListItem() = default;
    virtual std::ostream & print(std::ostream & os) const override;
    virtual FloatListItem * clone() const override;

private:
    float value_;
};

struct StringListItem : public ListItem
{
    explicit StringListItem(const std::string & value);
    virtual ~StringListItem() = default;
    virtual std::ostream & print(std::ostream & os) const override;
    virtual StringListItem * clone() const override;

private:
    std::string value_;
};


class BidirectionalList
{
public:
    BidirectionalList() = default;
    ~BidirectionalList();
    BidirectionalList(const BidirectionalList & other);
    BidirectionalList(BidirectionalList && other);
    BidirectionalList & operator= (const BidirectionalList & other );
    BidirectionalList & operator=(BidirectionalList && other);

    void clear();
    // insert item before pos; if pos == nullptr insert back
    void insert(ListItem * pos, ListItem * item);
    void push_front(ListItem * item);
    void push_back(ListItem * item);
    ListItem * erase(ListItem * item);
    void pop_back();
    void pop_front();
    std::ostream & print(std::ostream & os) const;

private:
    void addFirstItem(ListItem * item);

private:
    ListItem * first_ = nullptr;
    ListItem * last_  = nullptr;
};

std::ostream & operator << (std::ostream & os, ListItem * item);
std::ostream & operator << (std::ostream & os, const BidirectionalList & list);


#endif // BIDIRECTIONALLIST_H
