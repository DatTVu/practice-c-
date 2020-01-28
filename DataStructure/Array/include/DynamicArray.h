#pragma once
class DynamicArray
{
    //Data Members
    private:
        int m_size;
        int m_capacity;
        int* m_data;
    //Function Members
    public:
        DynamicArray(){
            m_size = 0;
            m_capacity = 8;
            m_data = new int[8];
        } //default constructor
        DynamicArray(int capacity);      
        ~DynamicArray(); //destructor
        bool is_empty();
        int item_at(int index);
        void pushback(int item);
        void insert(int item, int index);
        void prepend(int item);
        void popback();
        void delete_item(int index);
        void remove_item(int item);
        void find(int item);     
        void display();
    private:
        void resize(int new_capacity);
};

