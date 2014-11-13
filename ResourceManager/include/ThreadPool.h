#pragma once

#include <functional>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <Singleton.h>

namespace UnknownEngine
{
    namespace Core
    {
        class ThreadPool : public Singleton<ThreadPool, size_t>
        {
        public:
            ThreadPool(size_t workers_count);
            virtual ~ThreadPool();

            typedef std::function<void()> Task;

            bool pushTask(Task task);

        private:

            class Worker
            {
            public:
                explicit Worker();
                bool pushTask(Task &task);
                void join();

            private:
                typedef std::mutex LockPrimitive;

                void threadFunction();

                volatile bool is_shutdown;
                LockPrimitive lock;
                std::queue<Task> tasks;
                std::condition_variable wait_for_tasks_cv;
                std::condition_variable wait_for_availability_cv;
                std::thread worker_thread;
            };

            Worker& findWorker();

            typedef std::mutex LockPrimitive;

            LockPrimitive lock;
			volatile bool is_shutdown;
            size_t current_worker_id;
            std::vector<Worker> workers;
        };

    }
}