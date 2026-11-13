#include <thread>
#include "ThreadPool.h"
#include <gtest/gtest.h>

TEST(ThreadPooltest, constructs_empty) {
    ThreadPool pool{};
    EXPECT_TRUE(pool.empty());
}

TEST(ThreadPooltest, one_task) {
    ThreadPool pool{};
    int num = 0;
    pool.enqueue([&num](){num++;});
    while (!pool.empty()) {}
    EXPECT_EQ(num, 1);
}

TEST(ThreadPooltest, multiple_tasks) {
    ThreadPool pool{};
    int num = 0;
    pool.enqueue([&num](){num++;});
    pool.enqueue([&num](){num++;});
    pool.enqueue([&num](){num++;});
    while (!pool.empty()) {}
    EXPECT_EQ(num, 3);
}
