#include <iostream>
#include "ArrayQueue.h"
#include "ArrayQueue.cpp"
#include <thread>

void dequeue(ArrayQueue<int> &src)
{
    while (!src.empty())
    {
        int res = src.dequeue();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        src.display();
    }
}

void populate(ArrayQueue<int> &src, int numOfElement)
{
    for (int i = 1; i < numOfElement; ++i)
    {
        src.enqueue(i);
    }
}

int main()
{
    //Test copied constructor
    ArrayQueue<int> test;
    populate(test, 100);
    test.display();
    ArrayQueue<int> copiedTest = test;

    copiedTest.display();

    //Test full API
    _ASSERT(copiedTest.full() == true);
    _ASSERT(test.full() == true);

    //Test dequeue API on 2 threads
    std::thread dequeue_thread_1 = std::thread(dequeue, std::ref(test));
    std::thread dequeue_thread_2 = std::thread(dequeue, std::ref(test));
    dequeue_thread_1.join();
    dequeue_thread_2.join();
    _ASSERT(test.empty());

    //Test constructor with capacity
    ArrayQueue<int> capacityTest(10);
    _ASSERT(capacityTest.empty());
    populate(capacityTest, 20);
    capacityTest.display();
    _ASSERT(capacityTest.full());

    std::thread dequeue_thread_3 = std::thread(dequeue, std::ref(capacityTest));
    std::thread enqueue_thread_1 = std::thread(populate, std::ref(capacityTest), 10);
    dequeue_thread_3.join();
    enqueue_thread_1.join();
}