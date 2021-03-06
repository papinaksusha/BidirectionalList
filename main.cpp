#include <bidirectionallist.h>

#include <iostream>
#include <string>
#include <sstream>
#include <variant>

int main()
{
    //1. Зацикливание

    BidirectionalList list1;
    list1.push_back(1);
    std::cout << "list1: " << list1;

    //2. Зацикливание

    BidirectionalList list2;
    list2.push_front(1.1f);
    list2.push_front(2.2f);
    std::cout << "list2: " << list2;


    //3. Зацикливание

    BidirectionalList list3;
    std::cout << "list3: " << list3;
    list3.push_back(2.2f);
    list3.push_front(1.1f);
    std::cout << "list3: " << list3;

    //4. Падение

    BidirectionalList list4;
    list4.push_front(1);
    list4.clear();
    std::cout << "list4: " << list4;

    //5. Падение

    BidirectionalList list5;
    list5.push_front(1);
    list5.pop_front();
    std::cout << "list5: " << list5;

    BidirectionalList list6;
    list6.push_front(1);
    list6.pop_front();
    std::cout << "list6: " << list6;

    BidirectionalList list7;
    list7.push_back(1);
    list7.pop_front();
    std::cout << "list7: " << list7;

    BidirectionalList list8;
    list8.push_back(1);
    list8.pop_back();
    std::cout << "list8: " << list8;



//// My test
    std::cout << "\nMy tests\n\n";
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
