#include "LinkedList.h"
#include <iostream>
#include <exception>

struct OutOfRange: std::exception
{
    const char* what() const throw()
    {
        return "Out of Range";
    }
};

template <class T> 
LinkedList<T>::LinkedList() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_ptrHead = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
    std::lock_guard<std::mutex> lock(list.m_mutex);
    m_ptrHead = list.m_ptrHead;
    list.m_ptrHead = nullptr;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ListNode<T>* ptrCurrent = m_ptrHead;
    ListNode<T>* ptrNext = nullptr;

    while(ptrCurrent != nullptr)
    {
        ptrNext = ptrCurrent->GetNext();
        delete ptrCurrent;
        ptrCurrent = ptrNext;
    }
}

template <class T>
size_t LinkedList<T>::size()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return size_impl();
}

template <class T>
size_t LinkedList<T>::size_impl()
{
    size_t size = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    while (ptrCurrent != nullptr)
    {
        ptrCurrent = ptrCurrent->GetNext();
        ++size;
    }
    return size;
}

template <class T>
void LinkedList<T>::push_front(T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ListNode<T>* ptrNode = new ListNode<T>(val);
    ptrNode->SetNext(m_ptrHead);
    m_ptrHead = ptrNode;
}

template <class T>
void LinkedList<T>::front(T& val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        throw OutOfRange();
    val = m_ptrHead->GetData();
}

template <class T>
bool LinkedList<T>::empty()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return (m_ptrHead==nullptr);
}

template <class T>
void LinkedList<T>::pop_front(T& val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        throw OutOfRange();

    val = m_ptrHead->GetData();
    ListNode<T>* ptrNext = m_ptrHead->GetNext();
    delete m_ptrHead;
    m_ptrHead = ptrNext;
}

template <class T>
void LinkedList<T>::push_back(T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ListNode<T>* ptrNode = new ListNode<T>(val);
    if(m_ptrHead==nullptr)
    {
        m_ptrHead = ptrNode;
        return;
    }

    ListNode<T>* ptrCurrent = m_ptrHead;
    while (ptrCurrent->GetNext()!=nullptr)
    {
        ptrCurrent = ptrCurrent->GetNext();
    }

    ptrCurrent->SetNext(ptrNode);
}

template <class T>
void LinkedList<T>::back(T& val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        throw OutOfRange();

    ListNode<T>* ptrCurrent = m_ptrHead;
    while(ptrCurrent->GetNext()!=nullptr)
    {
        ptrCurrent = ptrCurrent->GetNext();
    }
    val = ptrCurrent->GetData();
}

template <class T>
void LinkedList<T>::pop_back(T& val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_ptrHead == nullptr)
        throw OutOfRange();

    ListNode<T>* ptrCurrent = m_ptrHead;
    ListNode<T>* ptrPrevious = nullptr;
    while(ptrCurrent->GetNext()!=nullptr)
    {
        ptrPrevious = ptrCurrent;
        ptrCurrent = ptrCurrent->GetNext();
    }
    val = ptrCurrent->GetData();
    delete ptrCurrent;
    if(ptrPrevious==nullptr)
        m_ptrHead = ptrPrevious;
    else
        ptrPrevious->SetNext(nullptr);
}

template <class T>
void LinkedList<T>::insert_before(int ndx, T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    int index_range_ = static_cast<int>(this->size_impl()) - 1;
    if(ndx > index_range_ || ndx < 0)
        throw OutOfRange();

    ListNode<T>* ptrInsertNode = new ListNode<T>(val);
    if (ndx == 0)
    {
        ListNode<T>* ptrNext = m_ptrHead->GetNext();
        m_ptrHead->SetNext(ptrInsertNode);
        ptrInsertNode->SetNext(ptrNext);
    }
    else
    {
        ListNode<T>* ptrCurrent = m_ptrHead;
        ListNode<T>* ptrPrevious = ptrCurrent;
        int ndxCurrent = 0;
        while (ndxCurrent != ndx)
        {
            ++ndxCurrent;
            ptrPrevious = ptrCurrent;
            ptrCurrent = ptrCurrent->GetNext();
        }

        ptrInsertNode->SetNext(ptrCurrent);
        ptrPrevious->SetNext(ptrInsertNode);
    }
}

template <class T>
void LinkedList<T>::insert_after(int ndx, T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    int index_range_ = static_cast<int>(this->size_impl()) - 1;
    if (ndx > index_range_ || ndx < 0)
        throw OutOfRange();
    
    int ndxCurrent = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    while(ndxCurrent != ndx)
    {
        ++ndxCurrent;
        ptrCurrent = ptrCurrent->GetNext();
    }

    ListNode<T>* ptrNode = new ListNode<T>(val);
    if(ptrCurrent == nullptr)
    {
        ptrNode->SetNext(nullptr);
    }
    else
    {
        ListNode<T>* ptrNext= ptrCurrent->GetNext();
        ptrNode->SetNext(ptrNext);
    }
    ptrCurrent->SetNext(ptrNode);
}

template <class T>
T LinkedList<T>::value_at(int ndx)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    int index_range_ = static_cast<int>(this->size_impl()) - 1;
    if(ndx > index_range_ || ndx < 0)
        throw OutOfRange();
    
    int ndxCurrent = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    while(ndxCurrent!=ndx)
    {
        ++ndxCurrent;
        ptrCurrent = ptrCurrent->GetNext();
    }
    
    return ptrCurrent->GetData();
}

template <class T>
void LinkedList<T>::erase(int ndx)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    erase_impl(ndx);
}

template <class T>
void LinkedList<T>::erase_impl(int ndx)
{
    int index_range_ = static_cast<int>(this->size_impl()) - 1;
    if (ndx > index_range_ || ndx < 0)
        throw OutOfRange();

    ListNode<T>** ptrCurrent = &m_ptrHead;
    int ndxCurrent = 0;
    while (ndxCurrent != ndx)
    {
        ++ndxCurrent;
        *ptrCurrent = (*ptrCurrent)->GetNext();
    }

    ListNode<T>* ptrDelNode = *ptrCurrent;
    *ptrCurrent = ptrDelNode->GetNext();
    delete ptrDelNode;
}

template <class T>
void LinkedList<T>::reverse()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        throw OutOfRange();
    
    ListNode<T>* ptrCur = m_ptrHead;
    ListNode<T>* ptrPrev = nullptr;
    while(ptrCur!=nullptr)
    {
        ListNode<T>* ptrNext = ptrCur->GetNext();
        ptrCur->SetNext(ptrPrev);
        ptrPrev = ptrCur;
        ptrCur = ptrNext;
    }
    
    m_ptrHead = ptrPrev;
}

template <class T>
void LinkedList<T>::remove_first_value(T value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ListNode<T>* ptrCur = m_ptrHead;
    int ndxCurrent = 0;
    while(ptrCur!=nullptr)
    {
        if(value == ptrCur->GetData())
        {
            erase_impl(ndxCurrent);
            break;
        }
        ptrCur = ptrCur->GetNext();
        ++ndxCurrent;
    }
}

template <class T>
void LinkedList<T>::display()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_ptrHead == nullptr)
    {
        std::cout << "List is emptied\n";
        return;
    }
    ListNode<T>* ptrCur = m_ptrHead;
    while(ptrCur!=nullptr)
    {
        std::cout<< ptrCur->GetData() << " -> ";
        ptrCur = ptrCur->GetNext();
    }
    std::cout<< "\n" ;
}