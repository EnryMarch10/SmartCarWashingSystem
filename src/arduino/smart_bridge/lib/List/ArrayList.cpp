#ifndef __ARRAY_LIST__CPP
#define __ARRAY_LIST__CPP

#include "ArrayList.h"

template<typename T>
void ArrayList<T>::checkDimension(void)
{
    if (arrayElements == arrayLength) {
        arrayLength += arrayLength / 2;
        T *newArray = new T[arrayLength];
        for (unsigned char i = 0; i < arrayElements; i++) {
            newArray[i] = array[i];
        }
        delete [] array;
        array = newArray;
    } else if ((arrayElements > startSize) && (arrayElements < arrayLength / 2)) {
        arrayLength = max(startSize, arrayLength / 2);
        T *newArray = new T[arrayLength];
        for (unsigned char i = 0; i < arrayElements; i++) {
            newArray[i] = array[i];
        }
        delete [] array;
        array = newArray;
    }
    assert(arrayElements < arrayLength);
}

template<typename T>
ArrayList<T>::ArrayList(const unsigned char startSize)
{
    this->startSize = startSize;
    arrayElements = 0;
    arrayLength = startSize;
    array = new T[arrayLength];
}

template<typename T>
T& ArrayList<T>::operator[](const unsigned char i)
{
    assert(i < arrayLength);
    return array[i];
}

template<typename T>
T& ArrayList<T>::get(const unsigned char i)
{
    return (*this)[i];
}

template<typename T>
unsigned char ArrayList<T>::add(const T& t)
{
    checkDimension();
    array[arrayElements] = t;
    return arrayElements++;
}

template<typename T>
bool ArrayList<T>::removeAt(const unsigned char i)
{
    if (i < arrayElements) {
        for (unsigned char j = i + 1; j < arrayElements; j++) {
            array[j - 1] = array[j];
        }
        arrayElements--;
        return true;
    }
    return false;
}

template<typename T>
bool ArrayList<T>::remove(const T& t)
{
    bool found = false;
    unsigned char offset = 1;
    for (unsigned char i = 0; i < arrayElements; i++) {
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

    return found;
}

template<typename T>
unsigned char ArrayList<T>::length(void)
{
    return arrayElements;
}

template<typename T>
bool ArrayList<T>::isEmpty(void)
{
    return length() == 0;
}

template<typename T>
bool ArrayList<T>::containsSomething(void)
{
    return !isEmpty();
}

template<typename T>
ArrayList<T>::~ArrayList(void)
{
    delete [] array;
}

#endif // __ARRAY_LIST__CPP
