#include <iostream>

#include "ArrayBasedQueueIterator.h"

using namespace std;

int main() {
    cout << "First iterator" << endl;
    ArrayBasedQueue arrayBasedQueue(3);
    arrayBasedQueue.push(1);
    arrayBasedQueue.push(2);
    arrayBasedQueue.push(3);
    ArrayBasedQueueIterator arrayBasedQueueIterator(arrayBasedQueue);
    arrayBasedQueueIterator.start();
    while (!arrayBasedQueueIterator.finish()) {
        cout << arrayBasedQueueIterator.getValue() << endl;
        arrayBasedQueueIterator.next();
    }
    arrayBasedQueue.clear();
    arrayBasedQueue.push(6);
    arrayBasedQueue.push(7);
    cout << "Second itetator" << endl;
    arrayBasedQueueIterator.start();
    while (!arrayBasedQueueIterator.finish()) {
        cout << arrayBasedQueueIterator.getValue() << endl;
        arrayBasedQueueIterator.next();
    }
    cout << "q front: " << arrayBasedQueue.front() << "\n";
    arrayBasedQueue.pop();
    cout << "q front: " << arrayBasedQueue.front() << "\n";
    arrayBasedQueue.pop();
    cout << "empty? " << boolalpha << arrayBasedQueue.isEmpty() << "\n";
    return 0;
}
