#include "ArrayQueue.h"
#include <exception>

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
    m_ptrData = new T[m_capacity];
}

template<class T>
ArrayQueue<T>::ArrayQueue(std::size_t max_capacity):
    m_capacity(max_capacity)
{
    m_ptrData = new T[m_capacity];
}

template<class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& src)
{
    //TO-DO perform a deep copy here and go back to change for linked list as well
}


template<class T>
void ArrayQueue<T>::enqueue(T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(full_impl())
    {
        return;
    }
    else
    {
        (*m_ptrData)[m_ndxTail] = val;
        ++m_ndxTail; //TO-DO: use % to wrap around
    }
}

template<class T>
T ArrayQueue<T>::dequeue()
{
    T result_;

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

