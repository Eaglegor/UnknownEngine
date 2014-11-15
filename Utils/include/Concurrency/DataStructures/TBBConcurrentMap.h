#pragma once

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <mutex>
#include <iostream>
#include <tbb/concurrent_unordered_map.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename K, typename V>
		class TBBConcurrentMap
		{
		public:
			
			void for_each(std::function<void(std::pair<const K,V>&)> action)
			{
				for(auto& iter : internal_map)
				{
					action(iter);
				}
			}
			
			bool insert(const std::pair<K, V>& val)
			{
				return internal_map.insert(val).second;
			}
			
			size_t erase(const K& key)
			{
				return internal_map.unsafe_erase(key);
			}
			
		private:
			tbb::concurrent_unordered_map<K, V> internal_map;
		};
	}
}