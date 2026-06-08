#include "HashTable.h"

using namespace std;

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t cap) : capacity(cap), _size(0) {
    table.resize(capacity);
}

template <typename K, typename V>
size_t HashTable<K, V>::hash(const K& key) const {
    return hash<K>{}(key) % capacity;
}

template <typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value) {
    size_t index = hash(key);
    
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    
    table[index].emplace_back(key, value);
    _size++;
}

template <typename K, typename V>
void HashTable<K, V>::remove(const K& key) {
    size_t index = hash(key);
    
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == key) {
            table[index].erase(it);
            _size--;
            return;
        }
    }
}

template <typename K, typename V>
V* HashTable<K, V>::find(const K& key) {
    size_t index = hash(key);
    
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            return &pair.second;
        }
    }
    return nullptr;
}

template <typename K, typename V>
V& HashTable<K, V>::operator[](const K& key) {
    V* found = find(key);
    if (found) {
        return *found;
    }
    insert(key, V());
    return *find(key);
}

template <typename K, typename V>
void HashTable<K, V>::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    _size = 0;
}

template <typename K, typename V>
bool HashTable<K, V>::empty() const {
    return _size == 0;
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
    return _size;
}

template <typename K, typename V>
Iterator<K, V> HashTable<K, V>::begin() {
    Iterator<K, V> it(this, 0, table[0].begin());
    if (!table[0].empty()) {
        return it;
    }
    it.findNextNonEmptyBucket();
    return it;
}

template <typename K, typename V>
Iterator<K, V> HashTable<K, V>::end() {
    return Iterator<K, V>(this, capacity, table[capacity - 1].end());
}

//iterator

template <typename K, typename V>
Iterator<K, V>::Iterator(HashTable<K, V>* ht, size_t idx, 
         typename list<pair<K, V>>::iterator it)
    : hashTable(ht), bucketIndex(idx), bucketIterator(it) {}

template <typename K, typename V>
void Iterator<K, V>::findNextNonEmptyBucket() {
    while (bucketIndex < hashTable->capacity && hashTable->table[bucketIndex].empty()) {
        bucketIndex++;
    }
    if (bucketIndex < hashTable->capacity) {
        bucketIterator = hashTable->table[bucketIndex].begin();
    }
}

template <typename K, typename V>
pair<K, V>& Iterator<K, V>::operator*() {
    return *bucketIterator;
}

template <typename K, typename V>
pair<K, V>* Iterator<K, V>::operator->() {
    return &(*bucketIterator);
}

template <typename K, typename V>
Iterator<K, V>& Iterator<K, V>::operator++() {
    ++bucketIterator;
    if (bucketIterator == hashTable->table[bucketIndex].end()) {
        bucketIndex++;
        findNextNonEmptyBucket();
    }
    return *this;
}

template <typename K, typename V>
Iterator<K, V> Iterator<K, V>::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename K, typename V>
bool Iterator<K, V>::operator==(const Iterator& other) const {
    if (bucketIndex >= hashTable->capacity && 
        other.bucketIndex >= other.hashTable->capacity) {
        return true;
    }
    return hashTable == other.hashTable && 
           bucketIndex == other.bucketIndex && 
           bucketIterator == other.bucketIterator;
}

template <typename K, typename V>
bool Iterator<K, V>::operator!=(const Iterator& other) const {
    return !(*this == other);
}