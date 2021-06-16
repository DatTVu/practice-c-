#include <iostream>
#include "HashTable.h"
#include "HashObject.cpp"
#include "utils.h"

namespace ADT {
	template<class T>
	HashTable<T>::HashTable() {
		for (std::size_t i = 0; i < m_capacity; ++i) {
			m_data[i] = HashObject<T>();
		}
	}

	template<class T>
	HashTable<T>::~HashTable() {
		delete[] m_data;
	}

	template<class T>
	HashTable<T>::HashTable(int capacity) : m_capacity(capacity) {
		for (std::size_t i = 0; i < m_capacity; ++i) {
			m_data[i] = HashObject<T>();
		}
	}

	template<class T>
	int HashTable<T>::Hash(const std::string& key, std::size_t capacity) {
		//This is djb2 hash function.
		int iKeyLength_ = static_cast<int>(key.length());
		int hashCode = 5381;
		for (int i = 0; i < iKeyLength_; ++i) {
			hashCode = hashCode * 33 ^ key[i];
		}
		return (hashCode % capacity);
	}

	template<class T>
	void HashTable<T>::Add(const std::string& key, const T& value) {
		++m_size;
		ResizeIfNeeded();
		int hashCode = Hash(key, m_capacity);
		ADT::HashFlag flag = m_data[hashCode].GetFlag();
		while (flag == ADT::HashFlag::OCCUPPIED) {
			hashCode = (hashCode + 1) % m_capacity;
			flag = m_data[hashCode].GetFlag();
		}
		m_data[hashCode].AddValue(key, value);
	}

	template<class T>
	bool HashTable<T>::IsExists(const std::string& key) {
		bool result = false;
		int hashCode = Hash(key, m_capacity);
		ADT::HashFlag flag = m_data[hashCode].GetFlag();
		int count = 0;
		while ((flag == ADT::HashFlag::DELETED || (flag == ADT::HashFlag::OCCUPPIED && m_data[hashCode].GetKey() != key))
			&& (count <= m_capacity)) {
			hashCode = (hashCode + 1) % m_capacity;
			++count;
		}
		if (m_data[hashCode].GetKey() == key) {
			result = true;
		}
		return result;
	}

	template<class T>
	T HashTable<T>::GetValue(const std::string& key) {
		int hashCode = Hash(key, m_capacity);
		ADT::HashFlag flag = m_data[hashCode].GetFlag();
		int count = 0;
		while ((flag == ADT::HashFlag::DELETED || (flag == ADT::HashFlag::OCCUPPIED && m_data[hashCode].GetKey() != key))
			&& (count <= m_capacity)) {
			hashCode = (hashCode + 1) % m_capacity;
			flag = m_data[hashCode].GetFlag();
			++count;
		}
		if (m_data[hashCode].GetKey() == key) {
			return m_data[hashCode].GetValue();
		}
		else {
			throw;
		}
 	}

	template<class T>
	void HashTable<T>::Remove(const std::string& key) {
		int hashCode = Hash(key, m_capacity);
		--m_size;
		ResizeIfNeeded();
		ADT::HashFlag flag = m_data[hashCode].GetFlag();
		int count = 0;
		while ((flag == ADT::HashFlag::DELETED || (flag == ADT::HashFlag::OCCUPPIED && m_data[hashCode].GetKey() != key))
			&& (count <= m_capacity)) {
			hashCode = (hashCode + 1) % m_capacity;
			flag = m_data[hashCode].GetFlag();
			++count;
		}
		if (m_data[hashCode].GetKey() == key) {
			m_data[hashCode].SetFlag(ADT::HashFlag::DELETED);
		}
		else {
			throw;
		}
	}

	template<class T>
	void HashTable<T>::ResizeIfNeeded() {
		std::size_t new_capacity = k_default_capacity;

		if (m_size > m_capacity * k_growth_factor) {
			new_capacity = m_capacity * 2;
		}
		else if (m_size <= m_capacity * k_shrink_factor) {
			new_capacity = m_capacity / 2 > k_default_capacity ? m_capacity / 2 : k_default_capacity;
		}
		else {
			return;
		}

		new_capacity = GetNextPrime(new_capacity);
		if (new_capacity == m_capacity)
			return;

		HashObject<T>* new_data = new HashObject<T>[new_capacity];
		for (std::size_t i = 0; i < new_capacity; ++i) {
			new_data[i] = HashObject<T>();
		}

		for (std::size_t i = 0; i < m_capacity; ++i) {
			const std::string& key = m_data[i].GetKey();
			int new_hash_code = Hash(key, new_capacity);
			while (new_data[new_hash_code].GetFlag() == ADT::HashFlag::OCCUPPIED) {
				new_hash_code = (new_hash_code + 1) % new_capacity;
			}
			new_data[new_hash_code].AddValue(key, m_data[i].GetValue());
		}

		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
		new_data = nullptr;
		
	}
}
