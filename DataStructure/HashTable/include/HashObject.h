#ifndef HASH_OBJECT_
#define HASH_OBJECT_
namespace ADT {

	enum HashFlag {
		EMPTY = 0,
		OCCUPPIED = 1,
		DELETED = 2,
	};

    template <class T> 
	class HashObject
	{
	public:
		HashObject() = default;
		~HashObject() = default;
		HashObject(const std::string& key, const T& value) : m_key(key), m_value(value) {}
		//Copy and Move are not allowed
		HashObject(const HashObject<T>& src) = delete;
		HashObject(HashObject<T>&& src) = delete;
		HashObject<T>& operator=(const HashObject<T>& src) = delete;
		HashObject<T>&& operator=(HashObject<T>&& src) = delete;
		//Method
		HashFlag GetFlag();
		void SetFlag(HashFlag flag);
		void AddValue(T value);
		T Get();
		std::string GetKey();
	private:
		std::string m_key = "";
		T m_value;
		HashFlag m_flag{ HashFlag::EMPTY };
	};
}

#endif // !HASH_OBJECT_


