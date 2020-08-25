#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"
#include <thread>

void produce_data(LinkedList<int>& list) 
{
    for (int i = 0; i < 1000; ++i) {
        list.push_back(i);
    }
    list.display();
}

void pop_member(LinkedList<int>& list) {
    while (list.size() != 0)
    {
        int pop_val;
        list.pop_back(pop_val);
        std::cout << "\nPopped value is: " << pop_val <<"\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    LinkedList<int> test_list = LinkedList<int>();
    std::thread t1 = std::thread(produce_data, std::ref(test_list));
    t1.join();
    std::thread t2 = std::thread(pop_member, std::ref(test_list));
    std::thread t3 = std::thread(pop_member, std::ref(test_list));
    t2.join();
    t3.join();
    test_list.display();
    system("pause");
}

