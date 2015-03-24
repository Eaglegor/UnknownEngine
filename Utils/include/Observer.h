#pragma once

#include <unordered_set>
#include <mutex>
#include <functional>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename ListenerType>
		class Observer
		{
			public:
				Observer():
				current_listener(nullptr),
				listener_to_remove(nullptr)
				{}
				
				typedef std::function< void ( ListenerType* ) > CallbackFunc;
				
				void addListener ( ListenerType* listener )
				{
					std::lock_guard<std::recursive_mutex> guard(lock);
					if(rehashNeeded())
					{
						std::lock_guard<std::mutex> rehash_guard(rehash_lock);
						listeners.emplace(listener);
					}
					else
					{
						listeners.emplace(listener);
					}
				}

				void removeListener ( ListenerType* listener )
				{
					std::lock_guard<std::recursive_mutex> guard(lock);
					if(listener == current_listener)
					{
						listener_to_remove = listener;
					}
					else
					{
						listeners.erase(listener);
					}
				}

				void doForAllListeners ( CallbackFunc callback )
				{
					std::lock_guard<std::recursive_mutex> guard(lock);
					std::lock_guard<std::mutex> rehash_guard(rehash_lock);
					for(ListenerType* listener : listeners)
					{
						if(listener_to_remove != nullptr)
						{
							listeners.erase(listener_to_remove);
							listener_to_remove = nullptr;
						}
						current_listener = listener;
						callback(listener);
					}
					if(listener_to_remove != nullptr)
					{
						listeners.erase(listener_to_remove);
						listener_to_remove = nullptr;
					}
				}
				
			private:
				bool rehashNeeded()
				{
					return listeners.size() + 1 > listeners.bucket_count() * listeners.max_load_factor();
				}
				
				std::unordered_set<ListenerType*> listeners;
				std::recursive_mutex lock;
				std::mutex rehash_lock;
								
				ListenerType* current_listener;
				ListenerType* listener_to_remove;
		};
	}
}
