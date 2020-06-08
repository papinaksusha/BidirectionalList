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

    list.print();
    list.pop_front();
    std::cout << "pop_front : ";
    list.print();
    list.pop_back();
    std::cout << "pop_back : ";
    list.print();
    list.erase(flItem);
    std::cout << "erase 15.5: ";
    list.print();

    list.clear();

    return 0;
}
