#pragma once
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include "iterator.h"

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    vector<list<pair<K, V>>> table;
    size_t capacity;
    size_t _size;

    //functional
    size_t hash(const K& key) const;

    friend class Iterator<K, V>;

public:
    HashTable(size_t cap = 10);
    
    void insert(const K& key, const V& value);
    void remove(const K& key);
    
    V* find(const K& key);
    const V* find(const K& key) const;
    
    V& operator[](const K& key);
    
    void clear();
    bool empty() const;
    size_t size() const;
    
    Iterator<K, V> begin();
    Iterator<K, V> end();
};