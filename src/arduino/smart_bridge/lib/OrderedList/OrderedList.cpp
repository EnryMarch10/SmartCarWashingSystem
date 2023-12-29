#ifndef __ORDERED_LIST__CPP
#define __ORDERED_LIST__CPP

#include "OrderedList.h"

/**
 * Searches value index with binary search, O(log(n)), in this ordered set.
*/
template<typename T, typename K>
int OrderedList<T, K>::binary_search(/*ArrayList<T>& list, */ T& item)
{
    int l = 0;
    int r = ArrayList<T>::length() - 1;
    if (l > r) {
        return ArrayList<T>::getErrorIndex();
    }
    const K target = valueFunc(item);
    while (l <= r) {
        const int m = (l + r) / 2;
        if (valueFunc(ArrayList<T>::get(m)) < target) {
            l = m + 1;
        } else if (valueFunc(ArrayList<T>::get(m)) > target) {
            r = m - 1;
        } else {
            if (ArrayList<T>::get(m) == item) {
                return m;
            }
            int i = m - 1;
            for (; (i >= 0) && (valueFunc(ArrayList<T>::get(i)) == target); i--) {
                if (ArrayList<T>::get(i) == item) {
                    return i;
                }
            }
            for (i = m + 1; (i < ArrayList<T>::length()) && (valueFunc(ArrayList<T>::get(i)) == target); i++) {
                if (ArrayList<T>::get(i) == item) {
                    return i;
                }
            }
            return ArrayList<T>::getErrorIndex();
        }
    }
    return ArrayList<T>::getErrorIndex();
}

/**
 * Searches nearest value index with binary search, O(log(n)), in this ordered set.
 *
 * Returns value index if it's yet present in the set, otherwise nearest
 * position of one of the closest elements in the set.
*/
template<typename T, typename K>
int OrderedList<T, K>::binary_search_nearest(/*ArrayList<T>& list, */ const K& target)
{
    int l = 0;
    int r = ArrayList<T>::length() - 1;
    if (l > r) {
        return ArrayList<T>::getErrorIndex();
    }
    Distance nearest = {ABS_DIFF(target, valueFunc(ArrayList<T>::get(l))), l};
    while (l <= r) {
        const int m = (l + r) / 2;
        const K value = valueFunc(ArrayList<T>::get(m));
        if (value != target) {
            // Updates best diff
            const K tmp = ABS_DIFF(target, valueFunc(ArrayList<T>::get(m)));
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
            return m;
        }
    }
    return nearest.index;
}

template<typename T, typename K>
unsigned char OrderedList<T, K>::add(T& t)
{
    int result = binary_search_nearest(valueFunc(t));
    if (result == ArrayList<T>::getErrorIndex()) {
        return ArrayList<T>::add(t);
    }

    const K target = valueFunc(t);

    // There could be multiple values with same value, this forces me to scan neighbors
    while ((result > 0) && (valueFunc(ArrayList<T>::get(result)) > target)) {
        result--;
    }
    while (valueFunc(ArrayList<T>::get(result)) <= target) {
        result++;
        if (result >= ArrayList<T>::length()) {
            return ArrayList<T>::add(t);
        }
    }

    T prev = ArrayList<T>::get(result);
    ArrayList<T>::get(result) = t;
    for (unsigned char i = result + 1; i < ArrayList<T>::length(); i++) {
        swap<>(prev, ArrayList<T>::get(i));
    }
    ArrayList<T>::add(prev);

    return result;
}

template<typename T, typename K>
bool OrderedList<T, K>::remove(T& t)
{
    return ArrayList<T>::removeAt(binary_search(t));
}

template<typename T, typename K>
OrderedList<T, K>::~OrderedList(void) { }

#endif // __ORDERED_LIST__CPP
