#include "data_structures/LinkedList.hpp"

int main()
{
    LinkedList<int> list;

    // Test pushBack
    std::cout << "=== Test pushBack ===" << std::endl;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushBack(40);
    std::cout << "Lista después de pushBack: ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test pushFront
    std::cout << "\n=== Test pushFront ===" << std::endl;
    list.pushFront(5);
    std::cout << "Lista después de pushFront(5): ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test insert
    std::cout << "\n=== Test insert ===" << std::endl;
    list.insert(2, 15);
    std::cout << "Lista después de insert(2, 15): ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test contains
    std::cout << "\n=== Test contains ===" << std::endl;
    std::cout << "¿Contiene 20? " << (list.contains(20) ? "Sí" : "No")
              << std::endl;
    std::cout << "¿Contiene 100? " << (list.contains(100) ? "Sí" : "No")
              << std::endl;

    // Test find
    std::cout << "\n=== Test find ===" << std::endl;
    if (list.find(15))
        std::cout << "Encontrado: 15" << std::endl;

    // Test removeFront
    std::cout << "\n=== Test removeFront ===" << std::endl;
    list.removeFront();
    std::cout << "Lista después de removeFront: ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test removeBack
    std::cout << "\n=== Test removeBack ===" << std::endl;
    list.removeBack();
    std::cout << "Lista después de removeBack: ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test remove (por valor)
    std::cout << "\n=== Test remove ===" << std::endl;
    bool removed = list.remove(15);
    std::cout << "¿Se removió 15? " << (removed ? "Sí" : "No") << std::endl;
    std::cout << "Lista después de remove(15): ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test erase (por índice)
    std::cout << "\n=== Test erase ===" << std::endl;
    bool erased = list.erase(1);
    std::cout << "¿Se borró índice 1? " << (erased ? "Sí" : "No") << std::endl;
    std::cout << "Lista después de erase(1): ";
    list.print();
    std::cout << "Tamaño: " << list.size() << std::endl;

    // Test copy constructor
    std::cout << "\n=== Test copy constructor ===" << std::endl;
    LinkedList<int> listCopy = list;
    std::cout << "Copia: ";
    listCopy.print();

    // Test move constructor
    std::cout << "\n=== Test move constructor ===" << std::endl;
    LinkedList<int> listMove = std::move(listCopy);
    std::cout << "Move: ";
    listMove.print();
    std::cout << "Original después de move (vacía): "
              << (listCopy.empty() ? "Sí" : "No") << std::endl;

    // Test empty
    std::cout << "\n=== Test clear ===" << std::endl;
    LinkedList<int> tempList;
    tempList.pushBack(1);
    tempList.pushBack(2);
    tempList.pushBack(3);
    std::cout << "Antes de clear: ";
    tempList.print();
    tempList.clear();
    std::cout << "¿Está vacía? " << (tempList.empty() ? "Sí" : "No")
              << std::endl;

    return 0;
}
