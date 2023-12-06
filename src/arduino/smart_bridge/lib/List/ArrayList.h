#ifndef __ARRAY_LIST__H
#define __ARRAY_LIST__H

#include "utils.h"

template<typename T>
class ArrayList {

public:
    ArrayList(void);
    T operator[](const int i);
    void add(const T t);
    void remove(const T t);
    int length(void);
    bool isEmpty(void);
    ~ArrayList(void);

private:
    T *array;
    int arrayLength, arrayElements;
    void checkDimension();

};

#include "ArrayList.cpp"

#endif // __ARRAY_LIST__H