#include <iostream>
#include "Deque.h"

int main() {
    Deque d;
    
    d.pushBack(10);
    d.pushBack(20);
    d.pushFront(5);
    d.pushFront(1);
    d.pushBack(30);
    
    std::cout << "Deque: ";
    IIterator& it = d.iterator();
    for (it.start(); !it.finish(); it.next()) {
        std::cout << it.getElem() << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Front: " << d.front() << std::endl;
    std::cout << "Back: " << d.back() << std::endl;
    std::cout << "Size: " << d.getCount() << std::endl;
    
    std::cout << "Pop front: " << d.popFront() << std::endl;
    std::cout << "Pop back: " << d.popBack() << std::endl;
    
    std::cout << "After pops: ";
    IIterator& it2 = d.iterator();
    for (it2.start(); !it2.finish(); it2.next()) {
        std::cout << it2.getElem() << " ";
    }
    std::cout << std::endl;
    
    d.clear();
    std::cout << "After clear, empty: " << (d.isEmpty() ? "yes" : "no") << std::endl;
    
    return 0;
}