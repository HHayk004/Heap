#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class Heap {
    public:
        Heap(bool mode = 0);
        Heap(const std::initializer_list<T>& list, bool mode = 0);
        
        Heap(const Heap&) = default;
        Heap(Heap&&) = default;

        ~Heap() = default;

        void setComp(bool (*comp_tmp) (const T&, const T&));

        void push(const T& val);
        void pop();
        void heapify(size_t index);

        T top() const;

        size_t left(size_t index) const;
        size_t right(size_t index) const;
        size_t parent(size_t index) const;

        size_t size() const;
        bool empty() const;

    protected:
        void buildHeap();

    protected:
        std::vector<T> vec;
        bool (*comp) (const T&, const T&);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Heap<U>& heap);
};

#include "heap.hpp"

#endif