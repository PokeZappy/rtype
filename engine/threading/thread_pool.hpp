/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-cyprien.diederichs
** File description:
** thread_pool.hpp
*/

#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

    void worker_thread();
};

#endif // THREAD_POOL_HPP
