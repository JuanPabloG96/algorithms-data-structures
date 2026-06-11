#include "data_structures/DoublyLinkedList.hpp"

#include <iostream>

int main()
{
    std::cout << "=== Creating list1 ===\n";

    DoublyLinkedList<int> list1;

    list1.pushBack(10);
    list1.pushBack(20);
    list1.pushBack(30);

    list1.pushFront(5);
    list1.pushFront(1);

    list1.print();

    std::cout << "\n=== Testing removeFront ===\n";

    list1.removeFront();
    list1.print();

    std::cout << "\n=== Testing removeBack ===\n";

    list1.removeBack();
    list1.print();

    std::cout << "\n=== Testing Copy Constructor ===\n";

    DoublyLinkedList<int> list2(list1);

    std::cout << "List2:\n";
    list2.print();

    std::cout << "\n=== Modifying original list1 ===\n";

    list1.pushBack(999);

    std::cout << "List1:\n";
    list1.print();

    std::cout << "\nList2 should remain unchanged:\n";
    list2.print();

    std::cout << "\n=== Testing Copy Assignment ===\n";

    DoublyLinkedList<int> list3;

    list3.pushBack(100);
    list3.pushBack(200);

    std::cout << "List3 before assignment:\n";
    list3.print();

    list3 = list1;

    std::cout << "\nList3 after assignment:\n";
    list3.print();

    std::cout << "\n=== Testing Move Constructor ===\n";

    DoublyLinkedList<int> list4(std::move(list1));

    std::cout << "List4 after move:\n";
    list4.print();

    std::cout << "\nList1 after being moved-from:\n";
    list1.print();

    std::cout << "\n=== Testing Move Assignment ===\n";

    DoublyLinkedList<int> list5;

    list5.pushBack(777);
    list5.pushBack(888);

    std::cout << "List5 before move assignment:\n";
    list5.print();

    list5 = std::move(list2);

    std::cout << "\nList5 after move assignment:\n";
    list5.print();

    std::cout << "\nList2 after being moved-from:\n";
    list2.print();

    std::cout << "\n=== End of program ===\n";

    return 0;
}
