/**
 * General config file to define state of running code.
*/
#ifndef __UTILS__
#define __UTILS__

#define __DEBUG__

#ifdef __DEBUG__
    #include <assert.h>
#endif

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

#define BAUD_RATE 9600

#endif