#pragma once
#include <list>
#include <utility>

using namespace std;

template <typename K, typename V>
class HashTable;

template <typename K, typename V>
class Iterator {
private:
    HashTable<K, V>* hashTable;
    size_t bucketIndex;
    typename list<pair<K, V>>::iterator bucketIterator;

    void findNextNonEmptyBucket();

public:
    Iterator(HashTable<K, V>* ht, size_t idx, 
             typename list<pair<K, V>>::iterator it);

    pair<K, V>& operator*();
    pair<K, V>* operator->();
    
    Iterator& operator++();
    Iterator operator++(int);
    
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
};