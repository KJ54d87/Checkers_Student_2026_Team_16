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
    int num = 0;
    std::mutex finished_mutex;
    finished_mutex.lock();

    pool.enqueue([&num](){num++;});
    pool.enqueue([&num](){num++;});
    pool.enqueue([&num](){num++;});
    pool.enqueue([&num, &finished_mutex](){++num; finished_mutex.unlock();});
    finished_mutex.lock();

    EXPECT_EQ(num, 4);
}
