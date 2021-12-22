//
// Created by Administrator on 2021/12/21.
//

#ifndef DATASTRUCTURE_TEMPLATES_VECTORDEMO_H_
#define DATASTRUCTURE_TEMPLATES_VECTORDEMO_H_

#pragma once
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace laobai {
typedef int Rank;
const int DEFAULT_CAPACITY = 5;

template<typename T>
class vector {
public:
    friend std::ostream &operator<<(std::ostream &os, const vector<T> &v) {
        for (Rank i = 0; i < v.m_size; ++i)
            os << v.m_data[i] << " ";
        return os;
    }

public:
    //构造函数和析构函数
    vector(int cap = DEFAULT_CAPACITY, int sz = 0, const T v = T());
    vector(const T *arr, int n) { copyFrom(arr, 0, n); }
    vector(const T *arr, Rank lo, Rank hi) { copyFrom(arr, lo, hi); }
    vector(const vector<T> &v) { copyFrom(v.m_data, 0, v.m_size); }
    vector(const vector<T> &v, Rank lo, Rank hi) { copyFrom(v.m_data, lo, hi); }
    ~vector() { delete[] m_data; }
    vector<T> &operator=(const vector<T> &v);

    //只读接口
    int capacity() const { return m_capacity; }
    int size() const { return m_size; }
    bool empty() const { return !m_size; }
    Rank find(const T &e) const;
    Rank find(const T &e, Rank lo, Rank hi) const;
    Rank search(const T &e) const;
    Rank search(const T &e, Rank lo, Rank hi) const;
    int disordered() const;
    //void print() const;


    //可写访问接口
    void push_back(const T &e) { insert(e); }
    void pop_back() { remove(m_size - 1); }
    T &operator[](Rank r) {
        assert(r >= 0 && r < m_size);
        return m_data[r];
    }
    Rank insert(Rank r, const T &e);
    Rank insert(const T &e);
    const T remove(Rank r);
    int remove(Rank lo, Rank hi);
    void clear();
    int deduplicate();
    int uniquify();
    void sort(Rank lo, Rank hi);
    void sort();
protected:
    void copyFrom(const T *data, Rank lo, Rank hi);
    void expand();
    void shrink();
    void bubbleSort(Rank lo, Rank hi);
    void selectSort(Rank lo, Rank hi);
    void insertSort(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mid, Rank hi);
    Rank binSearch(const T &e, Rank lo, Rank hi) const;
    Rank binSearch_impl1(const T &e, Rank lo, Rank hi) const;//失败返回-1
    Rank binSearch_impl2(const T &e, Rank lo, Rank hi) const;//失败返回-1
    Rank binSearch_impl3(const T &e, Rank lo, Rank hi) const;//失败返回不大于e的最大秩

private:
    int uniquify_impl1();
    int uniquify_impl2();
    static void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

protected:
    Rank m_capacity;
    Rank m_size;
    T *m_data;

};

template<typename T>
vector<T>::vector(int cap = DEFAULT_CAPACITY, int sz = 0, T v = T())
    : m_capacity(cap), m_size(sz) {
    m_data = new T[m_capacity];
    for (int i = 0; i < m_size; ++i)
        m_data[i] = v;
}

template<typename T>
inline vector<T> &vector<T>::operator=(const vector<T> &v) {
    if (m_data == v.m_data)
        return *this;
    delete[] m_data;
    copyFrom(v.m_data, 0, v.m_size);

    return *this;
}

template<typename T>
inline Rank vector<T>::find(const T &e) const {
    return find(e, 0, m_size);
}

template<typename T>
inline Rank vector<T>::find(const T &e, Rank lo, Rank hi) const {
    assert(lo >= 0 && hi <= m_size && lo < hi);
    while (--hi >= lo) {
        if (e == m_data[hi])
            return hi;
    }

    return -1;
}

template<typename T>
inline Rank vector<T>::search(const T &e) const {
    return search(e, 0, m_size);
}

template<typename T>
inline Rank vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return binSearch(e, lo, hi);
}

template<typename T>
inline int vector<T>::disordered() const {
    int ret = 0;
    for (int i = 1; i < m_size; ++i) {
        if (m_data[i - 1] > m_data[i])
            ++ret;
    }

    return ret;
}

/*template<typename T>
inline void vector<T>::print() const
{
    for (Rank i = 0; i < m_size; ++i)
        std::cout << m_data[i] << " ";
    std::cout << std::endl;
}*/

template<typename T>
inline Rank vector<T>::insert(Rank r, const T &e) {
    assert(r >= 0 && r <= m_size);

    expand();
    for (Rank i = m_size; i > r; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[r] = e;
    ++m_size;

    return r;
}

template<typename T>
inline Rank vector<T>::insert(const T &e) {
    return insert(m_size, e);
}

template<typename T>
inline const T vector<T>::remove(Rank r) {
    assert(r >= 0 && r < m_size);

    T ret = m_data[r];
    remove(r, r + 1);

    return ret;
}

template<typename T>
inline int vector<T>::remove(Rank lo, Rank hi) {
    assert(lo >= 0 && hi <= m_size && lo < hi);

    int ret = hi - lo;
    for (Rank i = hi; i < m_size; ++i) {
        m_data[lo++] = m_data[i];
    }

    m_size -= ret;
    shrink();

    return ret;
}

template<typename T>
inline void vector<T>::clear() {
    remove(0, m_size);
}

template<typename T>
inline int vector<T>::deduplicate() {
    int old_size = m_size;
    for (int i = 1; i < size();) {
        if (find(m_data[i], 0, i) != -1)
            remove(i);
        else
            ++i;
    }
    return old_size - m_size;
}

template<typename T>
inline int vector<T>::uniquify() {
    return uniquify_impl2();
}

template<typename T>
inline void vector<T>::sort(Rank lo, Rank hi) {
    srand(static_cast<unsigned int> (time(nullptr)));

    switch (rand() % 5) {
        case 0 :bubbleSort(lo, hi);
            break;
        case 1 :selectSort(lo, hi);
            break;
        case 2 :insertSort(lo, hi);
            break;
        case 3 :
        default:mergeSort(lo, hi);
            break;
    }
}

template<typename T>
inline void vector<T>::sort() {
    sort(0, m_size);
}

template<typename T>
inline void vector<T>::expand() {
    if (m_size == m_capacity) {
        T *old_data = m_data;
        if (m_capacity < DEFAULT_CAPACITY)
            m_capacity = DEFAULT_CAPACITY;
        m_data = new T[m_capacity <<= 1];
        copyFrom(old_data, 0, m_size);
        delete[] old_data;
    }
}

template<typename T>
inline void vector<T>::shrink() {
    if (m_size * 5 < m_capacity) {
        T *old_data = m_data;
        m_capacity = (m_capacity / 2 < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : (m_capacity >> 1);
        m_data = new T[m_capacity];
        //copyFrom(old_data, 0, m_size);
        for (int i = 0; i < m_size; ++i)
            m_data[i] = old_data[i];
        delete[] old_data;
    }
}

template<typename T>
inline void vector<T>::bubbleSort(Rank lo, Rank hi) {
    assert(lo >= 0 && hi <= m_size && lo < hi);

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (Rank i = lo + 1; i < hi; ++i) {
            if (m_data[i - 1] > m_data[i]) {
                swap(m_data[i - 1], m_data[i]);
                sorted = false;
            }
        }

        --hi;
    }
}

template<typename T>
inline void vector<T>::selectSort(Rank lo, Rank hi) {
    assert(lo >= 0 && hi <= m_size);
    for (int i = 0; i < m_size; ++i) {
        T min = m_data[i];
        Rank min_idx = i;
        for (int j = i + 1; j < m_size; ++j) {
            if (m_data[j] < min) {
                min = m_data[j];
                min_idx = j;
            }

        }
        swap(m_data[min_idx], m_data[i]);
    }
}

template<typename T>
inline void vector<T>::insertSort(Rank lo, Rank hi) {
    assert(lo >= 0 && hi <= m_size);

    for (Rank i = lo + 1; i < hi; ++i) {
        for (Rank j = i; j > lo; --j) {
            if (m_data[j] < m_data[j - 1])
                swap(m_data[j], m_data[j - 1]);
            else
                break;
        }
    }
}

template<typename T>
inline void vector<T>::mergeSort(Rank lo, Rank hi) {
    assert(lo >= 0 && hi <= m_size);
    if (1 < (hi - lo)) {
        Rank mid = (hi + lo) >> 1;
        mergeSort(lo, mid);
        mergeSort(mid, hi);
        merge(lo, mid, hi);
    }
}

template<typename T>
inline void vector<T>::merge(Rank lo, Rank mid, Rank hi) {
    assert(lo >= 0 && hi <= m_size && lo < mid && mid < hi);

    T *A = m_data + lo;
    Rank lb = mid - lo;
    T *B = new T[lb];
    T *C = m_data + mid;
    Rank lc = hi - mid;

    for (Rank i = 0; i < lb; ++i)
        B[i] = A[i];

    Rank i = 0;
    Rank j = 0;
    Rank k = 0;
    while ((j < lb) && (k < lc)) {
        if (B[j] < C[k])
            A[i++] = B[j++];
        else
            A[i++] = C[k++];
    }

    if (j >= lb) {
        while (k < lc)
            A[i++] = C[k++];
    }
    if (k >= lc) {
        while (j < lb)
            A[i++] = C[j++];
    }

    delete[] B;
}

template<typename T>
inline Rank vector<T>::binSearch(const T &e, Rank lo, Rank hi) const {
    srand(static_cast<unsigned int> (time(nullptr)));
    switch (2) {
        case 0 :return binSearch_impl1(e, lo, hi);
        case 1:return binSearch_impl2(e, lo, hi);
        case 2:
        default:return binSearch_impl3(e, lo, hi);
    }
}

template<typename T>
inline Rank vector<T>::binSearch_impl1(const T &e, Rank lo, Rank hi) const {
    assert(lo >= 0 && hi <= m_size);

    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        if (e == m_data[mid])
            return mid;
        else if (e < m_data[mid])
            hi = mid;
        else
            lo = mid + 1;
    }

    return -1;
}

template<typename T>
inline Rank vector<T>::binSearch_impl2(const T &e, Rank lo, Rank hi) const {
    assert(lo >= 0 && hi <= m_size);

    while (1 < (hi - lo)) {
        Rank mid = (hi + lo) >> 1;
        if (e < m_data[mid])
            hi = mid;
        else
            lo = mid;
    }

    return (e == m_data[lo]) ? lo : -1;
}

template<typename T>
inline Rank vector<T>::binSearch_impl3(const T &e, Rank lo, Rank hi) const {
    assert(lo >= 0 && hi <= m_size);

    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        (e < m_data[mid]) ? hi = mid : lo = mid + 1;
    }

    return --lo;
}

template<typename T>
inline int vector<T>::uniquify_impl1() {
    int ret = 0;
    for (Rank i = 0; i < m_size;) {
        Rank j = i + 1;
        while (j < m_size) {
            if (m_data[i] == m_data[j])
                ++j;
            break;
        }
        if (i + 1 != j) {
            ret += remove(i + 1, j);
            i = j;
        } else
            ++i;
    }

    shrink();
    return ret;
}

template<typename T>
inline int vector<T>::uniquify_impl2() {
    Rank i = 0;
    Rank j = 0;
    while (++j < m_size) {
        if (m_data[i] != m_data[j])
            m_data[++i] = m_data[j];
    }
    m_size = ++i;
    shrink();

    return j - i;
}

template<typename T>
void vector<T>::copyFrom(const T *data, Rank lo, Rank hi) {
    //m_capacity = ((hi - lo) > DEFAULT_CAPACITY / 2) ? ((hi - lo) << 1) : DEFAULT_CAPACITY;
    m_data = new T[m_capacity = (hi - lo) << 1];
    m_size = 0;
    while (lo < hi) {
        m_data[m_size++] = data[lo++];
    }
}
}

#endif //DATASTRUCTURE_TEMPLATES_VECTORDEMO_H_
