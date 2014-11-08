#include <stdafx.h>
#include <ThreadPool.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		ThreadPool* Singleton<ThreadPool>::instance = nullptr;

		ThreadPool::ThreadPool ( size_t workers_count ) :
			is_shutdown ( false ),
			current_worker_id ( 0 ),
			workers ( workers_count )
		{}

		ThreadPool::~ThreadPool()
		{
			{
				std::lock_guard<LockPrimitive> guard ( lock );
				is_shutdown = true;
			}
			for ( Worker & worker : workers )
			{
				worker.join();
			}
		}

		bool ThreadPool::pushTask ( UnknownEngine::Core::ThreadPool::Task task )
		{
			std::lock_guard<LockPrimitive> guard ( lock );
			if ( is_shutdown ) return false;
			Worker &worker = findWorker();
			return worker.pushTask ( task );
		}

		ThreadPool::Worker &ThreadPool::findWorker()
		{
			Worker& worker = workers[current_worker_id];
			current_worker_id = ( current_worker_id + 1 ) % workers.size();
			return worker;
		}


		ThreadPool::Worker::Worker() :
			is_shutdown ( false ),
			worker_thread ( &ThreadPool::Worker::threadFunction, this )
		{
		}

		void ThreadPool::Worker::threadFunction()
		{
			std::unique_lock <LockPrimitive> guard ( lock );

			while ( !is_shutdown || !tasks.empty() )
			{
				if ( !tasks.empty() )
				{
					Task task = tasks.front();
					tasks.pop();

					guard.unlock();

					task();

					guard.lock();
				}
				else
				{
					wait_for_tasks_cv.wait ( guard );
				}
			}
		}

		bool ThreadPool::Worker::pushTask ( ThreadPool::Task &task )
		{
			std::lock_guard<LockPrimitive> guard ( lock );
			if ( is_shutdown ) return false;
			tasks.push ( task );
			wait_for_tasks_cv.notify_all();
			return true;
		}

		void ThreadPool::Worker::join()
		{
			{
				std::lock_guard<LockPrimitive> guard ( lock );
				is_shutdown = true;
				wait_for_tasks_cv.notify_all();
			}
			worker_thread.join();
		}

	}
}
