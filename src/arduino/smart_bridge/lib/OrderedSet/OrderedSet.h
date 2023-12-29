#ifndef __ORDERED_SET__H
#define __ORDERED_SET__H

#include "utils.h"
#include "ArrayList.h"

class BaseOrderedSet {

public:
    static int getErrorIndex(void)
    {
        return -1;
    }

};

template<typename T, typename K>
class OrderedSet: public BaseOrderedSet {

public:
    OrderedSet(K (*const posStrategy)(T& value))
    {
        list = new ArrayList<T>();
        this->valueFunc = posStrategy;
    }
    OrderedSet(K (*const posStrategy)(T& value), const unsigned char startSize)
    {
        list = new ArrayList<T>(startSize);
        this->valueFunc = posStrategy;
    }
    T& operator[](const unsigned char i);
    T& get(const unsigned char i);
    T& getFirst(void);
    unsigned char getFirstPos(void);
    int add(T& t);
    bool removeAt(const unsigned char i);
    bool remove(T& t);
    unsigned char length(void);
    bool isEmpty(void);
    bool containsSomething(void);
    ~OrderedSet(void);

private:
    ArrayList<T> *list;
    K (*valueFunc)(T& value);
    typedef struct Distance
    {
        K diff;
        int index;
    }
    Distance;

    int binary_search(ArrayList<T>& array, T& item);
    int binary_search_nearest(ArrayList<T>& array, T& item);

};

#include "OrderedSet.cpp"

#endif // __ORDERED_ARRAY_LIST__H
