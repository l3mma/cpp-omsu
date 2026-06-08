#include <iostream>
#include "BSTree.h"

/*
   hello(3)
      /     \
 binary(1)   world(2)
                \
                 tree(1)
*/

int main() {
    BSTree dict;
    
    dict.insert("hello");
    dict.insert("world");
    dict.insert("hello");
    dict.insert("tree");
    dict.insert("world");
    dict.insert("hello");
    dict.insert("binary");
    
    std::cout << "Dictionary:" << std::endl;
    std::cout << dict << std::endl;
    
    std::cout << "Count of 'hello': " << dict.find("hello") << std::endl;
    std::cout << "Count of 'nonexistent': " << dict.find("nonexistent") << std::endl;
    std::cout << "Total words: " << dict.totalWords() << std::endl;
    
    dict.remove("hello");
    std::cout << "\nAfter removing one 'hello':" << std::endl;
    std::cout << dict << std::endl;
    
    dict.remove("binary");
    std::cout << "After removing 'binary':" << std::endl;
    std::cout << dict << std::endl;
    
    BSTree dict2 = dict;
    BSTree dict3;
    dict3 = dict;
    
    std::cout << "Copied dictionary:" << std::endl;
    std::cout << dict2 << std::endl;
    
    return 0;
}