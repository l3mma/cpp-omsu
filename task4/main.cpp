#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

int main() {
    HashTable<string, int> ht;
    
    ht.insert("apple", 5);
    ht.insert("banana", 3);
    ht.insert("orange", 7);
    
    cout << "Size: " << ht.size() << endl;
    cout << "Is empty? " << (ht.empty() ? "Yes" : "No") << endl;
    
    int* val = ht.find("apple");
    if (val) cout << "Found apple: " << *val << endl;
    
    cout << "\nAll elements:" << endl;
    for (auto it = ht.begin(); it != ht.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    
    ht.remove("orange");
    ht.clear();
    cout << "\nAfter clear - Size: " << ht.size() << endl;
    
    return 0;
}