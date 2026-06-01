#ifndef DEQUE_H
#define DEQUE_H

#include "AList.h"
#include "Iterator.h"
#include <cstddef>

struct Node {
    int _value;
    Node* _prev;
    Node* _next;

    Node(const int& t, Node* p, Node* n) : _value(t), _prev(p), _next(n) {}
};

class Deque : public IList {
private:
    Node* _buff;
    size_t _count;

public:
    class Iterator : public IIterator {
    private:
        Node* _curr;
        Node* _buff;
        
    public:
        Iterator(Node* start, Node* buff) : _curr(start), _buff(buff) {}
        Iterator(const Iterator& other) : _curr(other._curr), _buff(other._buff) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                _curr = other._curr;
                _buff = other._buff;
            }
            return *this;
        }
        
        void start() override { 
            _curr = _buff->_next; 
        }
        
        int getElem() override { 
            return _curr ? _curr->_value : 0; 
        }
        
        void next() override { 
            if (_curr) _curr = _curr->_next; 
        }
        
        bool finish() override { 
            return _curr == _buff; 
        }
        
        Node* getCurrent() const { return _curr; }
        void setCurrent(Node* node) { _curr = node; }
        Node* getBuff() const { return _buff; }
    };

    Deque();
    Deque(const Deque&);
    Deque& operator=(const Deque&);
    Deque(Deque&&);
    Deque& operator=(Deque&&);
    ~Deque();

    void pushFront(const int&);
    int front() const;
    int popFront();
    
    void pushBack(const int&);
    int back() const;
    int popBack();

    void pushAt(IIterator&, const int&) override;
    void deleteAt(IIterator&) override;
    IIterator& find(const int&) override;
    void clear() override;
    bool isEmpty() const override;
    size_t getCount() const override;
    IIterator& iterator() override;
};

#endif