#ifndef __MYQUEUE__
#define __MYQUEUE__

#include "utils.h"

template<typename T>
class Queue {

public:
    Queue(void);
    bool isEmpty(void);
    void enqueue(const T obj);
    T dequeue(void);
    ~Queue(void);

private:
    typedef struct Node
    {
        T item;
        struct Node* next;
        struct Node* prev;
    }
    Node;
    unsigned n;
    Node* first;
    Node* last;

};

// Implemented here because of known linker problems in case of separate functions implementation in .cpp file

template <typename T>
Queue<T>::Queue(void)
{
#ifdef __DEBUG__
    assert(sentinel != NULL);
#endif
    n = 0;
    first = last = NULL;
}

template <typename T>
bool Queue<T>::isEmpty(void)
{
    if (first != NULL)
    {
#ifdef __DEBUG__
        assert(s->n != 0);
#endif
        return false;
    }
    return true;
}

template <typename T>
void Queue<T>::enqueue(const T obj)
{
    Node* tmp = NULL;
    tmp = (Node *) malloc(sizeof(*tmp));
#ifdef __DEBUG__
    assert(tmp != NULL);
#endif
    tmp->item = obj;

    if ((first == NULL) && (last == NULL))
    {
        tmp->next = tmp->prev = tmp;
        first = tmp;
    }
    else if (last == NULL)
    {
        tmp->next = tmp->prev = first;
        first->prev = first->next = tmp;
        last = tmp;
    }
    else
    {
#ifdef __DEBUG__
        assert(s->first != NULL);
#endif
        tmp->next = last;
        tmp->prev = first;
        last->prev = first->next = tmp;
        last = tmp;
    }
    n++;
}

template <typename T>
T Queue<T>::dequeue(void)
{
    T result;
    Node* tmp;
#ifdef __DEBUG__
    assert(s != NULL);
    assert(s->first != NULL);
#endif
    result = first->item;

    if ((first != NULL) && (last != NULL))
    {
        last->prev = first->prev;
        first->prev->next = last;
        tmp = first;
        if (first->prev == last)
        {
            first = last;
            last = NULL;
        }
        else
        {
            first = first->prev;
        }
        free(tmp);
        n--;
    }
    else if (first != NULL)
    {
        free(first);
        first = NULL;
        n--;
    }
    return result;
}

template <typename T>
Queue<T>::~Queue(void)
{
    while (!isEmpty()) {
        dequeue();
    }
#ifdef __DEBUG__
    assert(s != NULL);
    assert((s->first == NULL) && (s->last == NULL));
#endif
}

#endif
