#include "ArrayQueue.h"
#include <exception>
#include <iostream>

struct OutOfRange: std::exception
{
    const char* what() const throw()
    {
        return "Out of Range";
    }
};

template<class T>
ArrayQueue<T>::ArrayQueue()
{
    m_ptrData = std::make_unique<T[]>(m_capacity);
}

template<class T>
ArrayQueue<T>::~ArrayQueue()
{
}

template<class T>
ArrayQueue<T>::ArrayQueue(std::size_t max_capacity):
    m_capacity(max_capacity)
{
    m_ptrData = std::make_unique<T[]>(m_capacity);
}

template<class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& src)
{
    std::lock_guard<std::mutex> lock(src.m_mutex);
    m_capacity = src.m_capacity;
    m_ptrData = std::make_unique<T[]>(m_capacity);
    for(size_t i = 0; i < src.m_capacity; ++i)
    {
        m_ptrData[i] = src.m_ptrData[i];
    }
}


template<class T>
void ArrayQueue<T>::enqueue(T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_size == m_capacity)
        return; 
    
    m_ptrData[m_ndxTail] = val;
    m_ndxTail = (m_ndxTail + 1) % m_capacity;
    ++m_size;
}

template<class T>
T ArrayQueue<T>::dequeue()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_size == 0)
        return;
    
    T result_ = m_ptrData[m_ndxHead];
    m_ndxHead = (m_ndxHead + 1) % m_capacity;
    --m_size;
    return result_;
}

template<class T>
bool ArrayQueue<T>::empty()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return (m_size == 0);
}

template<class T>
bool ArrayQueue<T>::full()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return full_impl();
}

template<class T>
void ArrayQueue<T>::display()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (std::size_t i = 0; i < m_capacity; ++i)
    {
        std::cout << m_ptrData[i] << " ";
    }
    std::cout <<"\n";
}
