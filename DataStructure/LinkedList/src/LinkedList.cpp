#include "LinkedList.h"
#include <iostream>
DynamicArray::DynamicArray(int capacity) :  m_capacity(capacity),
                                            m_size(0)                                            
{
    m_data = new int[capacity];
}

bool DynamicArray::is_empty(){
    if (m_size==0)
        return true;
    else
        return false;
}

DynamicArray::~DynamicArray() {  
    delete[] m_data;            
}

int DynamicArray::item_at(int index){
    if ((index + 1) > m_size) {
        std::cout << "Index is out of bound" << std::endl;
        return -1;
    }        
    else
        return m_data[index];
}

void DynamicArray::pushback(int item){
    if (m_size >= m_capacity){
        resize(2*m_capacity);       
    }        
    m_data[m_size] = item;
    ++m_size;
}

void DynamicArray::insert(int item, int index){
    if (index >= m_size || index < 0) {
        std::cout << "Invalid index" << std::endl;
        return;
    }
    if((m_size+1) >= m_capacity){
       resize(2*m_capacity);       
    }
    std::memmove(&m_data[index + 1], &m_data[index], sizeof(int)*(m_size-index+1));
    m_data[index] = item;
    ++m_size;
}

void DynamicArray::prepend(int item){
    insert(item, 0);
}

void DynamicArray::popback(){
    m_data[m_size-1] = NULL;
    --m_size;    
    if(m_size ==(m_capacity/4))
        resize(m_capacity/2);
}

void DynamicArray::delete_item(int index){
    if (index >= m_size || index < 0) {
        std::cout << "Invalid index" << std::endl;
        return;
    }   
    std::memmove(&m_data[index], &m_data[index+1], sizeof(int)*(m_size-index+1));
    m_data[m_size-1] = NULL;
    --m_size;
}

void DynamicArray::find(int item){
    for (int i =0; i<m_size; i++){
        if (m_data[i]==item)
            std::cout << "Found number "<< item<<" at index " << i <<std::endl;
    }
}

void DynamicArray::remove_item(int item) {
    for (int i = 0; i < m_size; i++) {
        if (m_data[i] == item)
            delete_item(i);
    }
}

void DynamicArray::resize(int new_capacity){
    int* temp_array = new int[new_capacity];    
    int* swap_array = nullptr;
    std::memcpy(temp_array, m_data, sizeof(int)*m_size);    
    swap_array = m_data;
    m_data = temp_array;
    temp_array = nullptr;
    delete[] swap_array;
    m_capacity = new_capacity;
}

void DynamicArray::display(){
    for (int i = 0; i < m_size; i++)
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << "" << std::endl;
}