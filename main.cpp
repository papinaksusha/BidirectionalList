#include <bidirectionallist.h>

#include <iostream>
#include <string>
#include <sstream>

int main()
{
    BidirectionalList list;

    list.push_front(new StringListItem("front"));
    list.push_back(new IntegerListItem(10));
    ListItem * flItem = new FloatListItem(15.5);
    list.push_back(flItem);
    list.insert(flItem, new StringListItem("str"));
    list.push_back(new IntegerListItem(100));
    list.push_back(new FloatListItem(100.3));

    std::cout << list;
    list.pop_front();
    std::cout << "pop_front : " << list;
    list.pop_back();
    std::cout << "pop_back : "  << list;
    list.erase(flItem);
    std::cout << "erase 15.5: " << list;

    BidirectionalList copy = list;
    std::cout << "copy: " << copy;
    copy.push_back(new StringListItem("Seven"));
    list = copy;
    std::cout << "list assign modified copy: " << list;

    BidirectionalList mvCopy(std::move(copy));
    std::cout << "movable copy: " << mvCopy << "copy is empty: " << copy;
    copy = std::move(mvCopy);
    std::cout << "copy: " << copy << "moveble copy is empty: " << mvCopy;

    return 0;
}
