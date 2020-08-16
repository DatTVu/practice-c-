#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <thread>
template <typename T>
class LinkedList
{
public:
    LinkedList() noexcept;
    ~LinkedList() noexcept;
    pushfront();
    front();
    popfront();
    pushback();
    back();
    popback();
    empty();
    insertbefore(int ndx);
    insertafter(int ndx);
    size();
    value_at();
    insert(int ndx, T value);
    erase(int ndx);
    reverse();
    remove_first_value(T value);
protected:
private:
    LinkedList* m_ptrNext;
    T m_data;
    std::mutex m_mutex;
};
#endif

