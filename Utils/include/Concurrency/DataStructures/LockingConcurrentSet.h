#pragma once

#include <unordered_set>
#include <functional>
#include <mutex>
#include <iostream>
#include <Spinlock.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T, typename LockPrimitive = Utils::Spinlock>
		class LockingConcurrentSet
		{
		public:
			LockingConcurrentSet():
			lock(mutex, std::defer_lock),
			write_locks(0)
			{}
			
			class Iterator
			{
			public:
				typedef typename std::unordered_set<T>::iterator internal_iterator_type;
				Iterator(LockingConcurrentSet* parent, internal_iterator_type iterator):
				parent(parent),
				internal_iterator(iterator)
				{
					parent->reserve_write_lock();
				}
				
				Iterator(const Iterator& iter):
				parent(iter.parent),
				internal_iterator(iter.internal_iterator)
				{
					parent->reserve_write_lock();
				}
				
				~Iterator()
				{
					parent->release_write_lock();
				}
				
				Iterator& operator++()
				{
					++internal_iterator;
					return *this;
				}
				
				Iterator operator++(int){
					Iterator old_iter(*this);
					++(*this);
					return old_iter;
				}
				
				const T& operator*() const
				{
					return *internal_iterator;
				}
				
				bool operator==(const Iterator& rhs)
				{
					return internal_iterator == rhs.internal_iterator;
				}
				
				bool operator!=(const Iterator& rhs)
				{
					return internal_iterator != rhs.internal_iterator;
				}
				
			private:
				LockingConcurrentSet *parent;
				internal_iterator_type internal_iterator;
			};

			Iterator begin()
			{
				return Iterator(this, internal_set.begin());
			}
			
			Iterator end()
			{
				return Iterator(this, internal_set.end());
			}
			
			template<typename... ConstructorArgs>
			bool emplace(ConstructorArgs&&... args)
			{
				std::lock_guard<LockPrimitive> guard(mutex);
				return internal_set.emplace(std::forward<ConstructorArgs>(args)...).second;
			}
			
			size_t erase(const T &value)
			{
				std::lock_guard<LockPrimitive> guard(mutex);
				return internal_set.erase(value);
			}
			
		private:
			void reserve_write_lock()
			{
				std::lock_guard<LockPrimitive> guard(write_lock_mutex);
				if(write_locks == 0)
				{
					lock.lock();
				}
				++write_locks;
			}
			
			void release_write_lock()
			{
				std::lock_guard<LockPrimitive> guard(write_lock_mutex);
				--write_locks;
				if(write_locks == 0)
				{
					lock.unlock();
				}
			}
			
			friend class Iterator;
			
			LockPrimitive mutex;
			LockPrimitive write_lock_mutex;
			std::unique_lock<LockPrimitive> lock;
			volatile size_t write_locks;
			
			std::unordered_set<T> internal_set;
		};
	}
}