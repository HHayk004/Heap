template <typename T>
std::ostream& operator<<(std::ostream& os, const Heap<T>& heap)
{
    for (const T& elem : heap.vec)
    {
        os << elem << ' ';
    }

    return os;
}

template <typename T>
Heap<T>::Heap(bool mode)
{
    if (!mode)
    {
        setComp([](const T& val1, const T& val2){return val1 > val2;});
    }

    else
    {
        setComp([](const T& val1, const T& val2){return val1 < val2;});
    }
}

template <typename T>
Heap<T>::Heap(const std::initializer_list<T>& list , bool mode)
{
    vec = list;

    if (!mode)
    {
        setComp([](const T& val1, const T& val2){return val1 > val2;});
    }

    else
    {
        setComp([](const T& val1, const T& val2){return val1 < val2;});
    }

    buildHeap();
}

template <typename T>
void Heap<T>::setComp(bool (*comp_tmp) (const T& val1, const T& val2))
{
    comp = comp_tmp;
}

template <typename T>
void Heap<T>::buildHeap()
{
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        heapify(i);
    }
}

template <typename T>
void Heap<T>::heapify(size_t index)
{
    if (index < vec.size() / 2)
    {
        size_t small_index = index;
        size_t left_index = left(index);
        size_t right_index = right(index);
        if (comp(vec[index], vec[left_index]))
        {
            small_index = left_index;
        }

        if (right_index < vec.size() && comp(vec[small_index], vec[right_index]))
        {
            small_index = right_index;
        }
    
        if (small_index != index)
        {
            std::swap(vec[index], vec[small_index]);
            heapify(small_index);
        }
    }
}

template <typename T>
void Heap<T>::push(const T& val)
{
    vec.push_back(val);
    size_t index = vec.size() - 1;
    while (index > 0)
    {
        size_t parent_index = parent(index);
        if (comp(vec[parent_index], vec[index]))
        {
            std::swap(vec[index], vec[parent_index]);
            index = parent_index;
        }

        else
        {
            break;
        }
    }
}

template <typename T>
void Heap<T>::pop()
{
    std::swap(vec[0], vec[vec.size() - 1]);
    vec.pop_back();
    heapify(0);
}

template <typename T>
T Heap<T>::top() const
{
    return vec[0];
}

template <typename T>
size_t Heap<T>::left(size_t index) const
{
    return 2 * index + 1;
}

template <typename T>
size_t Heap<T>::right(size_t index) const
{
    return 2 * index + 2;
}

template <typename T>
size_t Heap<T>::parent(size_t index) const
{
    return (index - 1) / 2;
}

template <typename T>
size_t Heap<T>::size() const
{
    return vec.size();
}

template <typename T>
bool Heap<T>::empty() const
{
    return vec.empty();
}