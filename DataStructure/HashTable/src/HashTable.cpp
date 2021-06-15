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
		delete[] m_data;
	}

	template<class T>
	HashTable<T>::HashTable(int capacity) : m_capacity(capacity) {
		for (std::size_t i = 0; i < m_capacity; ++i) {
			m_data[i] = HashObject<T>();
		}
	}

	template<class T>
	int HashTable<T>::Hash(const std::string& key) {
		//This is djb2 hash function.
		int iKeyLength_ = static_cast<int>(key.length());
		int hashCode = 5381;
		for (int i = 0; i < iKeyLength_; ++i) {
			hashCode = hashCode * 33 ^ key[i];
		}
		return (hashCode % m_capacity);
	}

	template<class T>
	void HashTable<T>::Add(const std::string& key, const T& value) {
		++m_size;
		ResizeIfNeeded();
		int hashCode = Hash(key);
		HashFlag flag = m_data[hashCode].GetFlag();
		while (flag == HashFlag::OCCUPPIED) {
			hashCode = (hashCode + 1) % m_capacity;
			flag = m_data[hashCode].GetFlag();
		}
		m_data[hashCode].AddValue(value);
	}

	template<class T>
	bool HashTable<T>::IsExists(const std::string& key) {
		bool result = false;
		int hashCode = Hash(key);
		HashFlag flag = m_data[hashCode].GetFlag();
		int count = 0;
		while ((flag == HashFlag::DELETED || (flag == HashFlag::OCCUPPIED && m_data[hashCode].GetKey() != key))
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
	T HashTable<T>::Get(const std::string& key) {
		int hashCode = Hash(key);
		HashFlag flag = m_data[hashCode].GetFlag();
		int count = 0;
		while ((flag == HashFlag::DELETED || (flag == HashFlag::OCCUPPIED && m_data[hashCode].GetKey() != key))
			&& (count <= m_capacity)) {
			hashCode = (hashCode + 1) % m_capacity;
			flag = m_data[hashCode].GetFlag();
			++count;
		}
		if (m_data[hashCode].GetKey() == key) {
			return m_data[hashCode].GetKey();
		}
		else {
			throw std::out_of_range;
		}
	}

	template<class T>
	void HashTable<T>::Remove(const std::string& key) {
		int hashCode = Hash(key);
		--m_size;
		ResizeIfNeeded();
		HashFlag flag = m_data[hashCode].GetFlag();
		int count = 0;
		while ((flag == HashFlag::DELETED || (flag == HashFlag::OCCUPPIED && m_data[hashCode].GetKey() != key))
			&& (count <= m_capacity)) {
			hashCode = (hashCode + 1) % m_capacity;
			flag = m_data[hashCode].GetFlag();
			++count;
		}
		if (m_data[hashCode].GetKey() == key) {
			m_data[hashCode].SetFlag(HashFlag::DELETED);
		}
		else {
			throw std::out_of_range;
		}
	}

	template<class T>
	void HashTable<T>::ResizeIfNeeded() {
		std::size_t new_capacity = k_default_capacity;

		if (m_size > m_capacity * k_growth_factor) {
			new_capacity = m_capacity * 2;
		}
		else if (m_size <= m_capacity * k_shrink_factor) {
			new_capacity = m_capacity / 2;
		}
		else {
			return;
		}

		HashObject<T>* new_data = new HashObject<T>[new_capacity];
		for (std::size_t i = 0; i < new_capacity; ++i) {
			new_data[i] = HashObject<T>();
		}

		for (std::size_t i = 0; i < m_capacity; ++i) {

		}
	}
}
