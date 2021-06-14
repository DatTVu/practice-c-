#include <iostream>
#include "HashObject.h"

namespace ADT {
	template <class T>
	bool HashObject<T>::IsNull() {
		if (m_flag == HashFlag::EMPTY) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	void HashObject<T>::SetFlag(HashFlag flag) {
		m_flag = flag;
	}

	template <class T>
	T HashObject<T>::Get() {
		return m_value;
	}
}
