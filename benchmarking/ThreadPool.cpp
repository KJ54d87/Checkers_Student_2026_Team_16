#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int num_threads){
    stop = false;
    tasks = std::queue<std::function<void()>>();
    for (int i = 0; i<num_threads; i++){
        threads.push_back(std::thread([this]{
            while (true){
                queue_mutex.lock();
                std::function<void()> func;
                if (!tasks.empty()){
                    std::cout<<"no way this activates\n";
                    func = tasks.front();
                    tasks.pop();
                } else {
                    if (stop) {
                        queue_mutex.unlock();
                        return;
                    }
                }
                queue_mutex.unlock();
                if (func) func(); //Causing a bad_function_call for some reason
            }            
        }));
    }
}
        //lock mutex
                    //Check if we can pop
                    // If no, check if stop is set
                    // If so, then return
                    // Otherwise, loop back up
                    // If we can pop, pop and run function.

ThreadPool::~ThreadPool(){
    queue_mutex.lock();
    stop = true;
    queue_mutex.unlock();
    for (int i = 0; i < threads.size(); i++){
        threads[i].join();
    }
}
void ThreadPool::enqueue(std::function<void()>){}
bool ThreadPool::empty(){
    return tasks.empty();
}

