#ifndef __ORDERED_LIST__H
#define __ORDERED_LIST__H

#include "utils.h"
#include "ArrayList.h"

template<typename T, typename K>
class OrderedList: public ArrayList<T> {

public:
    OrderedList(K (*const posStrategy)(T& value)) : ArrayList<T>()
    {
        // list = new ArrayList<T>();
        this->valueFunc = posStrategy;
    }
    OrderedList(K (*const posStrategy)(T& value), const unsigned char size) : ArrayList<T>(size)
    {
        // list = new ArrayList<T>(size);
        this->valueFunc = posStrategy;
    }
    unsigned char add(T& t);
    bool remove(T& t);
    ~OrderedList(void);

private:
    K (*valueFunc)(T& value);
    typedef struct Distance
    {
        K diff;
        int index;
    }
    Distance;

    int binary_search(T& item);
    int binary_search_nearest(const K& target);

};

#include "OrderedList.cpp"

#endif // __ORDERED_ARRAY_LIST__H
