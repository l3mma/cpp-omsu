#ifndef ARRAYBASEDQUEUE_H
#define ARRAYBASEDQUEUE_H

#include <cstddef>

class ArrayBasedQueue {
private:
    std::size_t _size;
    int _front;
    int _rear;
    int *_array;
public:
    ArrayBasedQueue();

    ArrayBasedQueue(const ArrayBasedQueue &);

    ArrayBasedQueue &operator=(const ArrayBasedQueue &);

    ArrayBasedQueue(ArrayBasedQueue &&);

    ArrayBasedQueue &operator=(ArrayBasedQueue &&);

    ~ArrayBasedQueue();

    explicit ArrayBasedQueue(std::size_t);

    void push(const int &);

    int pop();

    int front();

    std::size_t size() const;

    void clear();

    bool isEmpty() const;

    friend class ArrayBasedQueueIterator;
};

#endif
