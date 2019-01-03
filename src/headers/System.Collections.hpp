#ifndef _SYSTEM_COLLECTIONS_HPP
#define _SYSTEM_COLLECTIONS_HPP

#include "System.hpp"

//Based on:
//https://docs.microsoft.com/en-us/dotnet/api/system.collections?view=netframework-4.7.2

namespace System {
namespace Collections {
	template <typename A, typename B>
	class Pair : public System::Object {
		private:
			const A first;
			const B second;
		public:
			Pair(const A& key, const B& value) : first(key), second(value) {}
			const A& GetFirst () const {
				return first;
			};
			const B& GetSecond () const {
				return second;
			};
	};

	template <typename Key, typename Value>
	class KeyValuePair : private Pair<Key,Value> {
		public:
			KeyValuePair(const Key& key, const Value& value) : Pair<Key,Value>(key, value) {}
			const Key& GetKey () const {
				return Pair<Key,Value>::GetFirst();
			};
			const Value& GetValue () const {
				return Pair<Key,Value>::GetSecond();
			};
	};
	
	template <typename T>
	class IEnumerator : public System::Object {
		public:
			virtual void Reset() = 0;
			virtual bool HasNext() = 0;
			virtual void Next() = 0;
			virtual const T& Current() = 0;
	};
	
	template <typename T>
	class ICollection : public System::Object {
		public:
			virtual void Clear() = 0;
			virtual int Count() = 0;
			virtual IEnumerator<T> Iterator() = 0;
			//TODO add a begin & end specialization to work with range based for loops
	};
	
	template<typename A, typename B>
	class IComparator : public System::Object {
		public:
			virtual int Compare(const A& a, const B& b) = 0;
	};
	
	template<typename Key, typename Value>
	class IDictionary : public ICollection<KeyValuePair<Key,Value>>{
		public:
			virtual bool Put(const Key& key, const Value& value) = 0;
			virtual bool Contains(const Key& key) = 0;
			virtual void Remove(const Key& key) = 0;
	};
}
}

#endif