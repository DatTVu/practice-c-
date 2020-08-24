#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"

int main()
{
    std::cout << "Hello World!\n";
    LinkedList<int> test_list = LinkedList<int>();
    for (int i = 0; i < 15; ++i) {
        test_list.push_back(i);
    }
    test_list.display();
    for (int i = 0; i < 5; ++i)
    {
        int popped_value;
        test_list.pop_back(popped_value);
        std::cout << "Popped value is: " << popped_value << "\n";
    }
    test_list.display();
    system("pause");
}

