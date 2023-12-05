/**
 * General config file to define state of running code.
*/
#ifndef __UTILS__
#define __UTILS__

#include <Arduino.h>

// #define __DEBUG__

#ifdef __DEBUG__
    #include <assert.h>
#endif

#define TASK_BORN F("task born")
#define TASK_INIT F("task init")
#define TASK_DIE F("task die")
#define TASK_STOP F("task stop")
#define TASK_RESUME F("task resume")

#define XOR_SWAP(X, Y)  {\
                            (X) ^= (Y);\
                            (Y) ^= (X);\
                            (X) ^= (Y);\
                        }

#define TMP_SWAP(tmp, X, Y) {\
                                (tmp) = (X);\
                                (X) = (Y);\
                                (Y) = (tmp);\
                            }

template<class T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

void my_assert(unsigned char e);

#define BAUD_RATE 9600

#endif