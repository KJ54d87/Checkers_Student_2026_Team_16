#include <thread>
#include <iostream>
#include "ThreadPool.h"
#include <gtest/gtest.h>

TEST(ThreadPooltest, constructs_empty) {
    ThreadPool pool{};
    EXPECT_TRUE(pool.empty());
}

TEST(ThreadPooltest, one_task) {
    ThreadPool pool{};
    int num = 0;
    std::mutex finished_mutex;
    finished_mutex.lock();

    pool.enqueue([&num, &finished_mutex](){++num; finished_mutex.unlock();});
    finished_mutex.lock();


    EXPECT_EQ(num, 1);
}

TEST(ThreadPooltest, multiple_tasks) {
    ThreadPool pool{};
    const int tasks = 10;
    int num = 0;
    std::mutex finished_mutex[tasks];
    
    for (int i = 0; i < tasks; i++){
        finished_mutex[i].lock();
        pool.enqueue([&num, &finished_mutex, i](){++num; finished_mutex[i].unlock();});
    }

    for (int i = 0; i < tasks; i++) finished_mutex[i].lock();

    EXPECT_EQ(num, tasks);
}
