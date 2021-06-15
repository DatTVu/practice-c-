#include <iostream>
#include "HashObject.h"

namespace ADT {
	template <class T>
	HashFlag HashObject<T>::GetFlag() {
		return m_flag;
	}

	template <class T>
	void HashObject<T>::SetFlag(HashFlag flag) {
		m_flag = flag;
	}

	template <class T>
	void HashObject<T>::AddValue(T val) {
		m_value = val;
		m_flag = HashFlag::OCCUPPIED;
	}

	template <class T>
	T HashObject<T>::Get() {
		return m_value;
	}

	template <class T>
	std::string HashObject<T>::GetKey() {
		return m_key;
	}
	
}
