#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_
#include<thread>
#include<mutex>
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
        HashTable(const HashTable<T>& src);

        //Move Constructor is not allowed
        HashTable(HashTable<T>&& src) = delete;

        //Copy Assignment is not allowed
        HashTable& operator= (const HashTable<T>& src) = delete;

        //Move Assignment is not allowed
        HashTable& operator= (HashTable<T>&& src) = delete;
        
        //Transform the key into array index
        void Hash(const T& key);

        //Add a key to the hash table, if the key
        //already exists, update the value to the 
        //new value
        void Add(const std::string& key, const T& value);

        //Return true if key is in the tablek, false if key is
        //not inside the table
        bool IsExists(const std::string& key);

        //Return the value associated with the key
        T Get(const std::string& key);

        //Delete a key and its associated value from the HashTable
        void Remove(const std::string& key);

    //Data Members
    private:
        struct Node {
            std::string m_key;
            T m_value;
            Node() = default;
            Node(const std::string& key, const T& value) : m_key(key), m_value(value) {}
            bool IsNull();
        };                  
        //Default capacity should be an prime odd number to disperse
        //the keys evenly among the array slots
        constexpr std::size_t static k_default_capacity = 13;
        mutable std::mutex m_mutex;
        std::size_t m_capacity{ k_default_capacity };

    //Private Function Members
    private:
        void Resize();
};
#endif //HASH_TABLE_H_

