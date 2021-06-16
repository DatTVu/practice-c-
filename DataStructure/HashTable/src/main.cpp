#include <iostream>
#include "HashTable.h"
#include "HashTable.cpp"

int main()
{
    ADT::HashTable<std::string> hash_table;
    hash_table.Add("1", "1v");
    hash_table.Add("2", "2v");
    hash_table.Add("3", "3v");
    hash_table.Add("4", "4v");
    hash_table.Add("5", "5v");
    hash_table.Add("6", "6v");
    hash_table.Add("7", "7v");
    hash_table.Add("8", "8v");
    hash_table.Add("9", "9v");
    hash_table.Add("10", "10v");
    hash_table.Add("11", "11v");
    hash_table.Add("12", "12v");
    hash_table.Add("13", "13v");
    hash_table.Add("14", "14v");
    

    _ASSERT(hash_table.GetValue("1") == "1v");
    _ASSERT(hash_table.GetValue("2") == "2v");
    _ASSERT(hash_table.GetValue("3") == "3v");
    _ASSERT(hash_table.GetValue("4") == "4v");
    _ASSERT(hash_table.GetValue("5") == "5v");
    _ASSERT(hash_table.GetValue("6") == "6v");
    _ASSERT(hash_table.GetValue("7") == "7v");
    _ASSERT(hash_table.GetValue("8") == "8v");
    _ASSERT(hash_table.GetValue("9") == "9v");
    _ASSERT(hash_table.GetValue("10") == "10v");
    _ASSERT(hash_table.GetValue("11") == "11v");
    _ASSERT(hash_table.GetValue("12") == "12v");
    _ASSERT(hash_table.GetValue("13") == "13v");
    _ASSERT(hash_table.GetValue("14") == "14v");
    hash_table.Remove("10");
    _ASSERT(hash_table.GetValue("10") == "10v"); //this line should crash
    std::cout << "Hello World!\n";
    system("pause");
}

