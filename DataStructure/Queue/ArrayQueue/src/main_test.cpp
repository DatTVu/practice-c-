#include <iostream>
#include "ArrayQueue.h"
#include "ArrayQueue.cpp"

int main()
{
    ArrayQueue<int> test;
    for (int i = 0; i < 10; ++i)
    {
        test.enqueue(i);
    }
    test.display();   
    ArrayQueue<int> copiedTest = test;
    copiedTest.display();
}