#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <initializer_list>

template <typename T>
class Heap {
    public:
        Heap(bool mode = 0);
        Heap(const std::initializer_list<T>& list, bool mode = 0);
        
        Heap(const Heap&) = default;
        Heap(Heap&&) = default;

        ~Heap() = default;

        void setComp(std::function<bool(const T&, const T&) >tmp_comp);

        void push(const T& val);
        void pop();

        T top() const;

        size_t left(size_t index) const;
        size_t right(size_t index) const;
        size_t parent(size_t index) const;

        size_t size() const;
        bool empty() const;

    private:
        void heapify(size_t index, size_t size);
        void buildHeap();

    private:
        std::vector<T> vec;
        std::function<bool(const T&, const T&)> min = [](int val1, int val2) -> bool {return val1 < val2;};
        std::function<bool(const T&, const T&)> max = [](int val1, int val2) -> bool {return val1 > val2;};
        std::function<bool(const T&, const T&)> comp;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Heap<U>& heap);

    template <typename U>
    friend void heapSort(std::vector<U>& vec);
};

#include "heap.hpp"

#endif