#pragma once

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <mutex>
#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename K, typename V>
		class LockingConcurrentMap
		{
		private:
			typedef std::mutex LockPrimitive;
			
		public:
			
			void for_each(std::function<void(std::pair<const K,V>&)> action)
			{
				std::lock_guard<LockPrimitive> rehash_guard(rehash_lock);
				for(auto& iter : internal_map)
				{
					action(iter);
				}
			}
			
			bool insert(const std::pair<K, V>& val)
			{
				std::lock_guard<LockPrimitive> guard(concurrent_writings_lock);
				bool rehash_needed = internal_map.size() + 1 > internal_map.bucket_count() * internal_map.max_load_factor();
				if(rehash_needed)
				{
					std::lock_guard<LockPrimitive> rehash_guard(rehash_lock);
					return internal_map.insert(val).second;
				}
				else
				{
					return internal_map.insert(val).second;
				}
			}
			
			size_t erase(const K& key)
			{
				std::lock_guard<LockPrimitive> rehash_guard(rehash_lock);
				return internal_map.erase(key);
			}
			
		private:
			std::unordered_map<K, V> internal_map;
			LockPrimitive rehash_lock;
			LockPrimitive concurrent_writings_lock;
		};
	}
}