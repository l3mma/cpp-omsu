#ifndef ITERATOR_H
#define ITERATOR_H

class IIterator {
public: 
    virtual void start() = 0;
    virtual int getElem() = 0;
    virtual void next() = 0;
    virtual bool finish() = 0;
    virtual ~IIterator() {}
};

#endif