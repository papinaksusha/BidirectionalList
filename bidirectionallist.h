#ifndef BIDIRECTIONALLIST_H
#define BIDIRECTIONALLIST_H

#include <string>


struct ListItem
{
    virtual void print() const = 0;
    virtual ~ListItem() = default;

    ListItem* prev_ = nullptr;
    ListItem* next_ = nullptr;
};


struct IntegerListItem : public ListItem
{
    explicit IntegerListItem(int value);
    virtual ~IntegerListItem() = default;
    virtual void print() const override;

private:
    int value_;
};

struct FloatListItem : public ListItem
{
    explicit FloatListItem(float value);
    virtual ~FloatListItem() = default;
    virtual void print() const override;

private:
    float value_;
};

struct StringListItem : public ListItem
{
    explicit StringListItem(const std::string & value);
    virtual ~StringListItem() = default;
    virtual void print() const override;

private:
    std::string value_;
};


class BidirectionalList
{
public:
    BidirectionalList() = default;
    ~BidirectionalList();
    void clear();
    // insert item before pos; if pos == nullptr insert back
    void insert(ListItem * pos, ListItem * item);
    void push_front(ListItem * item);
    void push_back(ListItem * item);
    ListItem * erase(ListItem * item);
    void pop_back();
    void pop_front();
    void print() const;

private:
    void addFirstItem(ListItem * item);

private:
    ListItem * first_ = nullptr;
    ListItem * last_  = nullptr;
};


#endif // BIDIRECTIONALLIST_H
