#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <thread>
#include "ListNode.h"
template <class T>
class LinkedList
{
public:
    explicit LinkedList() noexcept;
    ~LinkedList();
    size_t size();
    void push_front(T val);
    void front(T& val);
    bool empty();
    void pop_front(T& val);
    void push_back(T val);
    void back(T& val);
    void pop_back(T& val);
    void insert_before(int ndx, T val);
    void insert_after(int ndx, T val);
    T value_at(int ndx);
    void erase(int ndx);
    void reverse();
    void remove_first_value(T value);
    void display();
private:
    ListNode<T>* m_ptrHead;
    std::mutex m_mutex;
};
#endif