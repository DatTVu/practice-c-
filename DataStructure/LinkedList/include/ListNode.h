#ifndef LIST_NODE_H_
#define LIST_NODE_H_

template <class T>
class ListNode
{
public:
    ListNode(){};
    ListNode(const T &val): m_data(val), m_ptrNext(nullptr){}
    ~ListNode(){};
    ListNode(const ListNode&) = delete;
    ListNode operator = (const ListNode&) = default;
    const T& GetData() {return m_data;}
    const ListNode<T>* GetNext() {return m_ptrNext;}
    SetData(const T& val){m_data = val};
    SetNext(ListNode<T>* ptr){m_ptrNext = ptr};
private:
    ListNode<T>* m_ptrNext;
    T            m_data;
};
#endif 
