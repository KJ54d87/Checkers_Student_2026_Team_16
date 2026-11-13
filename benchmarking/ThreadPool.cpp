#include "ThreadPool.h"

ThreadPool::ThreadPool(int num_threads){
    stop = true;
    tasks = std::queue<std::function<void()>>();
    //for (int i = 0; i<num_threads; i++){
    //    threads.push_back(std::thread([this]{
            //lock mutex
            //Check if we can pop
            // If no, check if stop is set
            // If so, then return
            // Otherwise, loop back up
            // If we can pop, pop and run function.
    //    }));
    //}
}

ThreadPool::~ThreadPool(){}
void ThreadPool::enqueue(std::function<void()>){}
bool ThreadPool::empty(){return true;}

