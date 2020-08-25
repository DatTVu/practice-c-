#include "LinkedList.h"
#include <iostream>
#include <exception>

struct empty_list: std::exception
{
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
    size_t size = 0;

    ListNode<T>* ptrCurrent = m_ptrHead;
    while(ptrCurrent != nullptr)
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
        throw empty_list();
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
        throw empty_list();

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
        throw empty_list();

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
        throw empty_list();

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
    if(m_ptrHead==nullptr && ndx > 0)
        throw empty_list();

    int ndxCurrent = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    ListNode<T>* ptrPrevious = nullptr;
    while(ptrCurrent->GetNext()!=nullptr)
    {
        if(ndxCurrent==ndx)
            break;
        else
        {
            ++ndxCurrent;
            ptrPrevious = ptrCurrent;
            ptrCurrent = ptrCurrent->GetNext();    
        }
    }

    if(ndxCurrent!=ndx)
        return;
    
    ListNode<T>* ptrNode = new ListNode<T>(val);
    ptrPrevious->SetNext(ptrNode);
    ptrNode->SetNext(ptrCurrent);
}

template <class T>
void LinkedList<T>::insert_after(int ndx, T val)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr && ndx>0)
        throw empty_list();
    
    int ndxCurrent = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    while(ptrCurrent->GetNext()!= nullptr)
    {
        if(ndxCurrent==ndx)
            break;
        else
        {
            ++ndxCurrent;
            ptrCurrent = ptrCurrent->GetNext();    
        }
    }

    if(ndxCurrent!=ndx)
        return;

    ListNode<T>* ptrNode = new ListNode<T>(val);
    ptrCurrent->SetNext(ptrNode);
    if(ptrCurrent == nullptr)
    {
        ptrNode->SetNext(nullptr);
    }
    else
    {
        ListNode<T>* ptrNext= ptrCurrent->GetNext();
        ptrNode->SetNext(ptrNext);
    }
}

template <class T>
T LinkedList<T>::value_at(int ndx)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        throw empty_list();
    
    int ndxCurrent = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    while(ptrCurrent->GetNext()!=nullptr)
    {
        if(ndxCurrent==ndx)
            break;
        else
        {
            ++ndxCurrent;
            ptrCurrent=ptrCurrent->GetNext();
        }
    }

    if(ndxCurrent!=ndx)
        return;

    T value = ptrCurrent->GetData();
    return value;
}

template <class T>
void LinkedList<T>::erase(int ndx)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        throw empty_list();

    int ndxCurrent = 0;
    ListNode<T>* ptrCurrent = m_ptrHead;
    ListNode<T>* ptrPrevious = nullptr;
    while(ptrCurrent->GetNext()!=nullptr)
    {
        if(ndxCurrent==ndx)
            break;
        else
        {
            ++ndxCurrent;
            ptrPrevious = ptrCurrent;
            ptrCurrent = ptrCurrent->GetNext();
        }
    }
    if(ndxCurrent!=ndx)
        return;
    
    
    if(ptrNext!=nullptr)
    {
        ListNode<T>* ptrNext = ptrCurrent->GetNext();
        ptrPrevious->SetNext(ptrNext);
    }
    else
    {
        ptrPrevious->SetNext(nullptr);
    }

    delete ptrCurrent;
}

template <class T>
void LinkedList<T>::reverse()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        return;
    
    ListNode<T>* ptrCur = head;
    ListNode<T>* ptrPrev = nullptr;
    while(ptrCur!=nullptr)
    {
        ListNode<T>* ptrNext = ptrCur->GetNext();
        ptrCur->SetNext(ptrPrev);
        ptrPrev = ptrCur;
        ptrCur = ptrNext;
    }

    return ptrPrev;
}

template <class T>
void LinkedList<T>::remove_first_value(T value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ListNode<T>* ptrCur = m_ptrHead;
    ListNode<T>* ptrPrev = m_ptrHead;
    while(ptrCur!=nullptr)
    {
        if(value == ptrCur->GetData())
        {
            ptrPrev->SetNext(ptrCur->GetNext());
            delete ptrCur;
            break;
        }
        ptrPrev = ptrCur;
        ptrCur = ptrCur->GetNext();
    }
}

template <class T>
void LinkedList<T>::display()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_ptrHead==nullptr)
        return;
    ListNode<T>* ptrCur = m_ptrHead;
    while(ptrCur!=nullptr)
    {
        std::cout<< ptrCur->GetData() << " -> ";
        ptrCur = ptrCur->GetNext();
    }
    std::cout<< "\n" ;
}