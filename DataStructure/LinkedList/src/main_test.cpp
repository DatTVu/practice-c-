#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"
#include <thread>

void push_back(LinkedList<int>& list, int nElementCnt) 
{
    for (int i = 0; i < nElementCnt; ++i) {
        list.push_back(i);
        int back_val_;
        list.back(back_val_);
        _ASSERT(back_val_ == i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void push_front(LinkedList<int>& list, int nElementCnt)
{
    for (int i = 0; i < nElementCnt; ++i) {
        list.push_front(i);
        int front_val_;
        list.front(front_val_);
        _ASSERT(front_val_ == i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void pop_back(LinkedList<int>& list) {
    int num_ = 0;
    while (list.size() != 0)
    {
        int pop_val;
        list.pop_back(pop_val);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        ++num_;
    }
    std::cout << "Number of popped back value: " << num_ << "\n";
}

void pop_front(LinkedList<int>& list)
{
    int num_ = 0;
    while (list.size() != 0)
    {
        int pop_val;
        list.pop_front(pop_val);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        ++num_;
    }
    std::cout << "Number of popped front value: " << num_ << "\n";
}

void reverse(LinkedList<int>& list)
{
    list.reverse();
}

int main()
{
#pragma region __CONSTRUCTOR_TEST__
    //Test Default Constructor and Size;
    LinkedList<int> test_list_ = LinkedList<int>();
    _ASSERT(test_list_.size() == 0);
    for (int i = 10; i > 0; --i)
    {
        test_list_.remove_first_value(i);
        //The line below should crash since the list empty and we are trying to 
        //remove the 1st element from empty list. Uncomment to test this
        //behavior
        //test_list_.erase(0);
    }

#pragma endregion

#pragma region __PUSH_AND_POP_API_TEST__
    //Test push back and push front in 2 different threads
    std::thread push_back_thread_ = std::thread(push_back, std::ref(test_list_), 50);
    std::thread push_front_thread_ = std::thread(push_front, std::ref(test_list_), 50);
    push_back_thread_.join();
    push_front_thread_.join();
    test_list_.display();
    _ASSERT(test_list_.size() == 100);

    //Test pop back and pop front in 2 different threads
    std::thread pop_back_thread_ = std::thread(pop_back, std::ref(test_list_));
    std::thread pop_front_thread_ = std::thread(pop_front, std::ref(test_list_));
    pop_back_thread_.join();
    pop_front_thread_.join();
    _ASSERT(test_list_.size() == 0);
#pragma endregion

#pragma region __REVERSE_API_TEST__
    //Prepare data again
    push_back(test_list_, 10);
    _ASSERT(test_list_.size() == 10);
    std::cout << "\n------------Before Reverse------------\n";
    test_list_.display();

    //Test reverse API on two different threads
    std::thread reverse_list_thread1_ = std::thread(reverse, std::ref(test_list_));
    std::thread reverse_list_thread2_ = std::thread(reverse, std::ref(test_list_));
    std::thread reverse_list_thread3_ = std::thread(reverse, std::ref(test_list_));
    reverse_list_thread1_.join();
    reverse_list_thread2_.join();
    reverse_list_thread3_.join();
    std::cout << "\n------------After Reverse------------\n";
    test_list_.display();
    int front_value_;
    int back_value_;
    test_list_.front(front_value_);
    test_list_.back(back_value_);
    _ASSERT(back_value_ == 0);
    _ASSERT(front_value_ == 9);
#pragma endregion

#pragma region __INSERT_AFTER_API_TEST__
    //Test insert before API
    int value_at_;
    test_list_.insert_before(0, 9);
    value_at_ = test_list_.value_at(0);
    _ASSERT(value_at_ == 9);
    //Insert at 0 pos: valid pos
    for (int i = 0; i < 10; ++i)
    {
        test_list_.insert_after(0, -i);
        
        value_at_ = test_list_.value_at(1);
        _ASSERT(value_at_ == -i);
    }
    std::cout << "\n------------After Insert------------\n";
    test_list_.display();
    //Insert at -1 pos: out of range pos
    //This should throw an exception
    //Uncomment to test this behavior

    /*
    for (int i = 0; i < 10; ++i)
    {
        test_list_.insert_after(-1, i);
        test_list_.display();
    }*/

    //Insert at list_size_ pos: out of range pos
    //This should throw an exception
    //Uncomment to test this behavior

    /*int list_size_ = static_cast<int>(test_list_.size());
    for (int i = 0; i < 10; ++i)
    {
        test_list_.insert_after(list_size_, i);
        test_list_.display();
    }*/

#pragma endregion

#pragma region __ERASE_API_TEST__
    test_list_.remove_first_value(9);
    test_list_.display();
    std::cout << "\n------------Delete by Remove------------\n";
    for (int i = 9; i > 0; --i)
    {
        test_list_.remove_first_value(-i);
        test_list_.display();
    }
    
    std::cout << "\n------------Delete by Erase------------\n";
    while (!test_list_.empty())
    {
        test_list_.erase(0);
        test_list_.display();
    }
    
    test_list_.display();
    _ASSERT(test_list_.empty());
#pragma endregion
    system("pause");
}


