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

ThreadPool::~ThreadPool(){
    stop = true;
    for (int i = 0; i < threads.size(); i++){
        threads[i].join();
    }
}
void ThreadPool::enqueue(std::function<void()> func){
    queue_mutex.lock();
    tasks.push(func);
    queue_mutex.unlock();
    
}

bool ThreadPool::empty(){
    return tasks.empty();
}

