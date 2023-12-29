#ifndef __ORDERED_SET__CPP
#define __ORDERED_SET__CPP

#include "OrderedSet.h"

/**
 * Searches value index with binary search, O(log(n)), in this ordered set.
*/
template<typename T, typename K>
int OrderedSet<T, K>::binary_search(ArrayList<T>& list, T& item)
{
    int l = 0;
    int r = list.length() - 1;
    if (l > r) {
        return getErrorIndex();
    }
    const K target = valueFunc(item);
    while (l <= r) {
        const int m = (l + r) / 2;
        if (valueFunc(list[m]) < target) {
            l = m + 1;
        } else if (valueFunc(list[m]) > target) {
            r = m - 1;
        } else {
            if (list[m] == item) {
                return m;
            }
            int i = m - 1;
            for (; (i >= 0) && (valueFunc(list[i]) == target); i--) {
                if (list[i] == item) {
                    return i;
                }
            }
            for (i = m + 1; (i < list.length()) && (valueFunc(list[i]) == target); i++) {
                if (list[i] == item) {
                    return i;
                }
            }
            return getErrorIndex();
        }
    }
    return getErrorIndex();
}

/**
 * Searches nearest value index with binary search, O(log(n)), in this ordered set.
 *
 * Returns value index if it's yet present in the set, otherwise nearest
 * position of one of the closest elements in the set.
*/
template<typename T, typename K>
int OrderedSet<T, K>::binary_search_nearest(ArrayList<T>& list, T& item)
{
    int l = 0;
    int r = list.length() - 1;
    if (l > r) {
        return getErrorIndex();
    }
    const K target = valueFunc(item);
    Distance nearest = {ABS_DIFF(target, valueFunc(list[l])), l};
    while (l <= r) {
        const int m = (l + r) / 2;
        const K value = valueFunc(list[m]);
        if (value != target) {
            // Updates best diff
            const K tmp = ABS_DIFF(target, valueFunc(list[m]));
            if (tmp < nearest.diff) {
                nearest.diff = tmp;
                nearest.index = m;
            }

            // Updates boundaries
            if (value < target) {
                l = m + 1;
            } else /* if (value > target) */ {
                r = m - 1;
            }
        } else {
            // Finds same if yet present or last of the nearest
            if (list[m] == item) {
                return m;
            }
            int i = m - 1;
            for (; (i >= 0) && (valueFunc(list[i]) == target); i--) {
                if (list[i] == item) {
                    return i;
                }
            }
            for (i = m + 1; (i < list.length()) && (valueFunc(list[i]) == target); i++) {
                if (list[i] == item) {
                    return i;
                }
            }
            return i - 1;
        }
    }
    return nearest.index;
}

template<typename T, typename K>
T& OrderedSet<T, K>::getFirst(void)
{
    return (*this)[getFirstPos()];
}

template<typename T, typename K>
unsigned char OrderedSet<T, K>::getFirstPos(void)
{
    return 0;
}

template<typename T, typename K>
T& OrderedSet<T, K>::get(const unsigned char i)
{
    return (*list)[i];
}

template<typename T, typename K>
T& OrderedSet<T, K>::operator[](const unsigned char i)
{
    return (*this)[i];
}

template<typename T, typename K>
int OrderedSet<T, K>::add(T& t)
{
    int result = binary_search_nearest(*list, t);
    if (result == getErrorIndex()) {
        return list->add(t);
    }
    if (list->get(result) == t) {
        return getErrorIndex();
    }

    const K target = valueFunc(t);

    // There could be multiple values with same value, this forces me to scan neighbors
    while ((result > 0) && (valueFunc((*list)[result]) > target)) {
        result--;
    }
    while (valueFunc((*list)[result]) <= target) {
        result++;
        if (result >= list->length()) {
            return list->add(t);
        }
    }

    T prev = list->get(result);
    list->get(result) = t;
    for (unsigned char i = result + 1; i < list->length(); i++) {
        swap<>(prev, (*list)[i]);
    }
    list->add(prev);

    return result;
}

template<typename T, typename K>
bool OrderedSet<T, K>::removeAt(const unsigned char i)
{
    return list->removeAt(i);
}

template<typename T, typename K>
bool OrderedSet<T, K>::remove(T& t)
{
    const int i = binary_search(*list, t);
    return i != getErrorIndex() ? list->removeAt(i) : false;
}

template<typename T, typename K>
unsigned char OrderedSet<T, K>::length(void)
{
    return list->length();
}

template<typename T, typename K>
bool OrderedSet<T, K>::isEmpty(void)
{
    return list->isEmpty();
}

template<typename T, typename K>
bool OrderedSet<T, K>::containsSomething(void)
{
    return !isEmpty();
}

template<typename T, typename K>
OrderedSet<T, K>::~OrderedSet(void)
{
    delete list;
}

#endif // __ORDERED_SET__CPP
