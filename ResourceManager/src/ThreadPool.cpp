#include <ThreadPool.h>
#include <system_error>

namespace UnknownEngine
{
    namespace Core
    {

        ThreadPool::Worker::Worker(size_t tasks_limit):
        is_shutdown(false),
        is_available(true),
        tasks_count_limit(tasks_limit),
        worker_thread(&ThreadPool::Worker::threadFunction, this)
        {
        }

        void ThreadPool::Worker::threadFunction()
        {
            std::unique_lock <LockPrimitive> guard(this->lock);

            while(!is_shutdown || !tasks.empty())
            {
                while (tasks.empty())
                {
                    wait_for_tasks_cv.wait(this->lock);
                }

                Task task = tasks.front();
                tasks.pop();

                if(tasks.size() == tasks_count_limit - 1 )
                {
                    is_available = true;
                    wait_for_availability_cv.notifyAll();
                }
                guard.unlock();

                task();

                guard.lock();
            }
        }

        bool ThreadPool::pushTask(Task &task)
        {
            std::unique_lock<LockPrimitive> guard(lock);
            if(is_shutdown) return false;
            Worker &worker = findWorker();
            worker->pushTask(task);
        }

        void ThreadPool::Worker::pushTask(ThreadPool::Task &task) {
            std::unique_lock<LockPrimitive> guard(lock);
            while(!is_available)
            {
                wait_for_availability_cv.wait(lock);
            }
            tasks.push(task);
            if(tasks_count == tasks_limit)
            {
                is_available = false;
            }
            wait_for_tasks_cv.notifyAll();
        }

        void ThreadPool::Worker::join()
        {
            {
                std::unique_lock<LockPrimitive> guard(lock);
                is_shutdown = true;
            }
            worker_thread.join();
        }

        ThreadPool::Worker &ThreadPool::findWorker() {
            current_worker_id = current_worker_id + 1 % workers.size();
            return workers[current_worker_id];
        }

        bool ThreadPool::Worker::isIdle() {
            std::unique_lock<LockPrimitive> guard(lock);
            return tasks.empty();
        }

        ThreadPool::ThreadPool(size_t workers_count, size_t worker_tasks_limit):
        workers(workers_count, Worker(worker_tasks_limit))
        {}

        virtual ThreadPool::~ThreadPool()
        {
            for(Worker& worker: workers)
            {
                worker.join();
            }
        }

    }
}