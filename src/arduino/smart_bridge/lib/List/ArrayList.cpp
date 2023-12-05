#ifndef __ARRAY_LIST__CPP
#define __ARRAY_LIST__CPP

#include "ArrayList.h"

#define DEFAULT_SIZE 5

template<typename T>
void ArrayList<T>::checkDimension(void)
{
    if (arrayElements == arrayLength) {
        arrayLength *= 2;
        T *newArray = new T[arrayLength];

        for (int i = 0; i < arrayElements; i++) {
            newArray[i] = array[i];
        }

        delete [] array;
        array = newArray;
    } else if ((arrayElements > DEFAULT_SIZE) && (arrayElements < arrayLength / 2)) {
        arrayLength = max(DEFAULT_SIZE, arrayLength / 2);
        T *newArray = new T[arrayLength];

        for (int i = 0; i < arrayElements; i++) {
            newArray[i] = array[i];
        }

        delete [] array;
        array = newArray;
    }
}

template<typename T>
ArrayList<T>::ArrayList(void)
{
    arrayElements = 0;
    arrayLength = DEFAULT_SIZE;
    array = new T[arrayLength];
}

template<typename T>
T ArrayList<T>::operator[](const int i)
{
    return array[i];
}

template<typename T>
void ArrayList<T>::add(const T t)
{
    checkDimension();
    array[arrayElements++] = t;
}

template<typename T>
void ArrayList<T>::remove(const T t)
{
    bool found = false;
    int offset = 1;
    for (int i = 0; i < arrayElements; i++) {
        if (found) {
            if (array[i] != t) {
                array[i - offset] = array[i];
            } else {
                offset++;
            }
        } else if (array[i] == t) {
            found = true;
        }
    }
    if (found) {
        arrayElements -= offset;
    }
    checkDimension();
}

template<typename T>
int ArrayList<T>::length(void)
{
    return arrayElements;
}

template<typename T>
bool ArrayList<T>::isEmpty(void)
{
    return length() == 0;
}

template<typename T>
ArrayList<T>::~ArrayList(void)
{
    delete [] array;
}

#endif // __ARRAY_LIST__CPP
