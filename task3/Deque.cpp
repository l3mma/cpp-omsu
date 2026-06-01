#include "Deque.h"
#include <stdexcept>
#include <algorithm>

Deque::Deque() : _count(0) {
    _buff = new Node(0, nullptr, nullptr);
    _buff->_next = _buff;
    _buff->_prev = _buff;
}

Deque::Deque(const Deque& other) : _count(0) {
    _buff = new Node(0, nullptr, nullptr);
    _buff->_next = _buff;
    _buff->_prev = _buff;
    
    Node* current = other._buff->_next;
    while (current != other._buff) {
        pushBack(current->_value);
        current = current->_next;
    }
}

Deque& Deque::operator=(const Deque& other) {
    if (this != &other) {
        Deque temp(other);
        std::swap(_buff, temp._buff);
        std::swap(_count, temp._count);
    }
    return *this;
}

Deque::Deque(Deque&& other)  
    : _buff(other._buff), _count(other._count) {
    other._buff = nullptr;
    other._count = 0;
}

Deque& Deque::operator=(Deque&& other)  {
    if (this != &other) {
        clear();
        delete _buff;
        _buff = other._buff;
        _count = other._count;
        other._buff = nullptr;
        other._count = 0;
    }
    return *this;
}

Deque::~Deque() {
    clear();
    delete _buff;
}

void Deque::pushFront(const int& value) {
    Node* newNode = new Node(value, _buff, _buff->_next);
    _buff->_next->_prev = newNode;
    _buff->_next = newNode;
    _count++;
}

int Deque::front() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return _buff->_next->_value;
}

int Deque::popFront() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    Node* toDelete = _buff->_next;
    int value = toDelete->_value;
    _buff->_next = toDelete->_next;
    toDelete->_next->_prev = _buff;
    delete toDelete;
    _count--;
    return value;
}

void Deque::pushBack(const int& value) {
    Node* newNode = new Node(value, _buff->_prev, _buff);
    _buff->_prev->_next = newNode;
    _buff->_prev = newNode;
    _count++;
}

int Deque::back() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return _buff->_prev->_value;
}

int Deque::popBack() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    Node* toDelete = _buff->_prev;
    int value = toDelete->_value;
    _buff->_prev = toDelete->_prev;
    toDelete->_prev->_next = _buff;
    delete toDelete;
    _count--;
    return value;
}

void Deque::pushAt(IIterator& it, const int& value) {
    // каст к классам наследованным
    Iterator& iter = dynamic_cast<Iterator&>(it);
    Node* current = iter.getCurrent();
    
    if (current == _buff) {
        pushBack(value);
        iter.setCurrent(_buff->_prev);
    } else {
        Node* newNode = new Node(value, current->_prev, current);
        current->_prev->_next = newNode;
        current->_prev = newNode;
        _count++;
        iter.setCurrent(newNode); 
    }
}

void Deque::deleteAt(IIterator& it) {
    Iterator& iter = dynamic_cast<Iterator&>(it);
    Node* toDelete = iter.getCurrent();
    
    if (toDelete == _buff) return;
    
    iter.next();
    toDelete->_prev->_next = toDelete->_next;
    toDelete->_next->_prev = toDelete->_prev;
    delete toDelete;
    _count--;
}

IIterator& Deque::find(const int& value) {
    Node* current = _buff->_next;
    while (current != _buff && current->_value != value) {
        current = current->_next;
    }
    Iterator* it = new Iterator(current, _buff);
    return *it;
}

void Deque::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

bool Deque::isEmpty() const {
    return _count == 0;
}

size_t Deque::getCount() const {
    return _count;
}

IIterator& Deque::iterator() {
    Iterator* it = new Iterator(_buff->_next, _buff);
    return *it;
}