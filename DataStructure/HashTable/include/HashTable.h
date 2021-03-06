#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_
#include <thread>
#include <mutex>
#include "HashObject.h"

namespace ADT {
    constexpr std::size_t k_default_capacity = 13;
    constexpr float k_growth_factor = 0.5;
    constexpr float k_shrink_factor = 0.2;

    template <class T>
    class HashTable
    {
        //Function Members
    public:
        //Default constructor
        HashTable();

        //Default destructor
        ~HashTable();

        //Constructor 
        explicit HashTable(int capacity);

        //Copy Constructor is allowed
        HashTable(const HashTable<T>& src) = delete;

        //Move Constructor is not allowed
        HashTable(HashTable<T>&& src) = delete;

        //Copy Assignment is not allowed
        HashTable& operator= (const HashTable<T>& src) = delete;

        //Move Assignment is not allowed
        HashTable& operator= (HashTable<T>&& src) = delete;

        //Transform the key into array index
        int Hash(const std::string& key, std::size_t capacity);

        //Add a key to the hash table, if the key
        //already exists, update the value to the 
        //new value
        void Add(const std::string& key, const T& value);

        //Return true if key is in the tablek, false if key is
        //not inside the table
        bool IsExists(const std::string& key);

        //Return the value associated with the key
        T GetValue(const std::string& key);

        //Delete a key and its associated value from the HashTable
        void Remove(const std::string& key);

        //Data Members
    private:
        HashObject<T>* m_data{ new HashObject<T>[k_default_capacity] };
        //Default capacity should be an prime odd number to disperse the keys evenly among the array slots
        std::size_t m_capacity{ k_default_capacity };
        std::size_t m_size{ 0 };

        //Private Function Members
    private:
        void ResizeIfNeeded();
    };
}
#endif //HASH_TABLE_H_

