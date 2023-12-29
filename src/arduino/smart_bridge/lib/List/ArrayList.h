#ifndef __ARRAY_LIST__H
#define __ARRAY_LIST__H

#include "utils.h"

template<typename T>
class ArrayList {

public:
    ArrayList(void) : ArrayList(6) { }
    ArrayList(const unsigned char startSize);
    T& operator[](const unsigned char i);
    T& get(const unsigned char i);
    unsigned char add(const T& t);
    bool removeAt(const unsigned char i);
    bool remove(const T& t);
    unsigned char length(void);
    bool isEmpty(void);
    bool containsSomething(void);
    ~ArrayList(void);

private:
    unsigned char startSize;
    unsigned char arrayLength, arrayElements;
    T *array;

    void checkDimension();

};

#include "ArrayList.cpp"

#endif // __ARRAY_LIST__H
