#include <iostream>
#include "HashTable.h"

namespace ADT {
	template<class T>
	HashTable<T>::HashTable() {
		for (std::size_t i = 0; i < m_capacity; ++i) {
			m_data[i] = HashObject<T>();
		}
	}

	template<class T>
	HashTable<T>::~HashTable() {

	}

	template<class T>
	HashTable<T>::HashTable(int capacity) : m_capacity(capacity) {

	}

	template<class T>
	int HashTable<T>::Hash(const std::string& key) {
		//This is djb2 hash function.
		std::lock_guard<std::mutex> lock(m_mutex);
		int iKeyLength_ = static_cast<int>(key.length());
		int hashCode = 5381;
		for (int i = 0; i < iKeyLength_; ++i) {
			hashCode = hashCode * 33 ^ key[i];
		}
		return (hashCode % m_capacity);
	}

	template<class T>
	void HashTable<T>::Add(const std::string& key, const T& value) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_size++;
		if (m_size > m_capacity) {
			Resize();
		}
		int hashCode = Hash(key);
		if(*m_data[hashCode].IsNull())

	}

	template<class T>
	bool HashTable<T>::IsExists(const std::string& key) {
		std::lock_guard<std::mutex> lock(m_mutex);
	}

	template<class T>
	T HashTable<T>::Get(const std::string& key) {
		std::lock_guard<std::mutex> lock(m_mutex);
	}

	template<class T>
	void HashTable<T>::Remove(const std::string& key) {
		std::lock_guard<std::mutex> lock(m_mutex);
	}

	template<class T>
	void HashTable<T>::Resize() {

	}
}
