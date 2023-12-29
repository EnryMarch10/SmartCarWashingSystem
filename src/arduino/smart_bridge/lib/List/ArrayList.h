#ifndef __ARRAY_LIST__H
#define __ARRAY_LIST__H

#include "utils.h"

template<typename T>
class ArrayList {

public:
    ArrayList(void) : ArrayList(6) { }
    ArrayList(const unsigned char size);
    T& operator[](const unsigned char i);
    T& get(const unsigned char i);
    T& getFirst(void);
    T& getLast(void);
    unsigned char getFirstPos(void);
    unsigned char getLastPos(void);
    virtual unsigned char add(T& t);
    bool removeAt(const unsigned char i);
    virtual bool remove(T& t);
    unsigned char length(void);
    bool isEmpty(void);
    bool containsSomething(void);
    virtual ~ArrayList(void);

protected:
    int getErrorIndex(void);
    bool removeAt(const int i);

private:
    unsigned char startSize;
    unsigned char arrayLength, arrayElements;
    T *array;

    void checkDimension();

};

#include "ArrayList.cpp"

#endif // __ARRAY_LIST__H
