#pragma once

#include <functional>
#include <queue>
#include <vector>
#inlcude <mutex>
#include <condition_variable>
#include <thread>

namespace UnknownEngine
{
    namespace Core
    {
        class ThreadPool
        {
        public:
            ThreadPool(size_t workers_count, size_t worker_tasks_limit);
            virtual ~ThreadPool();

            typedef std::function<void()> Task;

            void pushTask(Task &task);

        private:

            class Worker
            {
            public:
                explicit Worker(size_t tasks_limit);
                bool pushTask(Task &task);
                void join();

            private:
                typedef std::mutex LockPrimitive;

                void threadFunction();

                volatile bool is_available;
                volatile bool is_shutdown;
                LockPrimitive lock;
                std::queue<Task> tasks;
                std::condition_variable wait_for_tasks_cv;
                std::condition_variable wait_for_availability_cv;
                size_t tasks_count_limit;
                std::thread worker_thread;
            };

            Worker& findWorker();

            typedef std::mutex LockPrimitive;

            LockPrimitive lock;
            size_t current_worker_id;
            std::vector<Worker> workers;
        };

    }
}