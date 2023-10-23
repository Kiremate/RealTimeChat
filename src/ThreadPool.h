#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    void enqueueJob(std::function<void()> job);

private:
    std::vector<std::jthread> workers;
    std::queue<std::function<void()>> jobs;

    std::mutex jobsMutex;
    std::condition_variable condition;

    void workerThread();
};

ThreadPool::ThreadPool(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { this->workerThread(); });
    }
}

ThreadPool::~ThreadPool() {
    // jthread takes care of thread interruption and joining
}

void ThreadPool::enqueueJob(std::function<void()> job) {
    {
        std::lock_guard<std::mutex> lock(jobsMutex);
        jobs.push(std::move(job));
    }
    condition.notify_one();
}

void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(jobsMutex);

            condition.wait(lock, [this] { return !jobs.empty(); });

            job = std::move(jobs.front());
            jobs.pop();
        }
        job();  // Execute the job
    }
}
