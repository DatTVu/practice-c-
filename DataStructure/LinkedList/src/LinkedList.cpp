#include "LinkedList.h"
#include <iostream>
#include <exception>

struct empty_list: std::exception
{
    const char* what() const throw();
};

template <class T> 
LinkedList<T>::LinkedList()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_ptrHead = nullptr;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    //to consider this for thread safe
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
    while(ptrCurrent->GetNext()!=nullptr)
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
    if(m_ptrHead == nullptr)
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
void erase(int ndx);
template <class T>
void reverse();
template <class T>
void remove_first_value(T value);
template <class T>
void display();