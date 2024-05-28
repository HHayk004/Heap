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
    mode ? setComp(max) : setComp(min);
}

template <typename T>
Heap<T>::Heap(const std::initializer_list<T>& list , bool mode)
{
    vec = list;

    mode ? setComp(max) : setComp(min);

    buildHeap();
}

template <typename T>
void Heap<T>::setComp(std::function<bool(const T&, const T&)> tmp_comp)
{
    comp = tmp_comp;
}

template <typename T>
void Heap<T>::buildHeap()
{
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        heapify(i, vec.size());
    }
}

template <typename T>
void Heap<T>::heapify(size_t index, size_t size)
{
    if (index < size / 2)
    {
        size_t i = index;
        size_t left_index = left(index);
        size_t right_index = right(index);
        if (!comp(vec[i], vec[left_index]))
        {
            i = left_index;
        }

        if (right_index < size && !comp(vec[i], vec[right_index]))
        {
            i = right_index;
        }
    
        if (i != index)
        {
            std::swap(vec[index], vec[i]);
            heapify(i, size);
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
        if (!comp(vec[parent_index], vec[index]))
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
    heapify(0, vec.size());
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

template <typename T>
void heapSort(std::vector<T>& vec)
{
    Heap<T> heap(1);
    heap.vec = std::move(vec);

    heap.buildHeap();

    for (int i = heap.size() - 1; i > 0; --i)
    {
        std::swap(heap.vec[0], heap.vec[i]);
        heap.heapify(0, i);
    }

    vec = std::move(heap.vec);
}