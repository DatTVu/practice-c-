#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include <thread>
#include <mutex>
#include <memory>
template <class T>
class ArrayQueue{
    private:
        constexpr std::size_t static k_default_capacity = 16;
        std::size_t m_ndxHead = 0;
        std::size_t m_ndxTail = 0;
        std::unique_ptr<T[]> m_ptrData;
        mutable std::mutex m_mutex;
        size_t m_size{0};
        size_t m_capacity{k_default_capacity};
    public:
        ArrayQueue();
        ~ArrayQueue();
        explicit ArrayQueue(size_t max_capacity);
        ArrayQueue(const ArrayQueue<T>& src);
        ArrayQueue(ArrayQueue<T>&& src) = delete;
        ArrayQueue &operator= (const ArrayQueue<T>& src) = delete;
        ArrayQueue &operator= (ArrayQueue<T>&& src) = delete;
        bool empty();
        bool full();
        void enqueue(T val);
        T dequeue();
        T top();
        void display();

    friend void swap(ArrayQueue<T>& lhs, ArrayQueue<T>& rhs) noexcept;
};
#endif