#ifndef THREAD_POOl
#define THREAD_POOL

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

//Stolen off of geeks for geeks lol

class ThreadPool{
    public:
        ThreadPool(int num_threads=std::thread::hardware_concurrency());
        ~ThreadPool();
        void enqueue(std::function<void()>);
        bool empty();

    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mutex;
        bool stop;
};

#endif
