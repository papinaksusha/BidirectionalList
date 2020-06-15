#include <bidirectionallist.h>

#include <iostream>
#include <string>
#include <sstream>
#include <variant>

int main()
{
    BidirectionalList list;

    list.push_front(std::string("front"));
    list.push_back(10);
    list.push_back(10.1f);

    std::cout << "list: " << list;

    BidirectionalList copy = list;
    std::cout << "copy: " << copy;

    copy.push_back(777);
    copy.push_front(555.555f);

    std::cout << "copy after push_back and push_front: " << copy;

    list.pop_back();
    list.pop_front();

    std::cout << "list after pop_back and pop_front: " << list;

    std::cout << "list front and back: " << list.front() << " " << list.back() << '\n';
    std::cout << "copy front and back: " << copy.front() << " " << copy.back() << '\n';

    list.clear();

    std::cout << "is list empty after clear? " << list.empty() << '\n';
    std::cout << "copy size " << copy.size() << '\n';

    BidirectionalList mvCopy(std::move(copy));
    std::cout << "movable copy: " << mvCopy << "is copy empty after move?: " << copy.empty() << '\n';
    copy = std::move(mvCopy);
    std::cout << "copy after operator= (&& mvCopy): " << copy << "is moveble copy empty after move?: " << mvCopy.empty() << '\n';

    BidirectionalList::const_iterator it = copy.erase(++copy.begin());

    std::cout << "copy after erase second: " << copy << "next after erase element: " << *it  << " copy size: " << copy.size() << '\n';

    copy.insert(++copy.begin(), 3);
    std::cout << "copy after insert int 3 after first: " << copy;
    copy.insert(++copy.begin(), 3.3f);
    std::cout << "copy after insert float 3.3 after first: " << copy;
    BidirectionalList::const_iterator it2 = copy.insert(--copy.end(), std::string("3str"));
    std::cout << "copy after insert string before last: " << copy << "copy size: " << copy.size() << " insert value: " << *it2 << '\n';


    return 0;
}
