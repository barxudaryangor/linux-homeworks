#include "parralel_scheduler.h"

// Constructor: Initializes the scheduler with the specified number of threads
parallel_scheduler::parallel_scheduler(std::size_t numThreads) {
    for (std::size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(&parallel_scheduler::task_thread, this);
    }
}

// Destructor: Ensures proper cleanup of threads
parallel_scheduler::~parallel_scheduler() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        stop = true;
    }

    // Notifies all threads to wake up and check for the stop condition
    condVar.notify_all();

    // Joins all threads to wait for their completion before destroying the scheduler
    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

// Worker thread function that executes tasks
void parallel_scheduler::task_thread() {
    while (true) {
        Task task;

        {
            std::unique_lock<std::mutex> lock(mutex);

            // Waits for a task or stop signal
            condVar.wait(lock, [this] { return stop || !tasks.empty(); });

            // Checks if the thread should stop
            if (stop && tasks.empty()) {
                return;
            }

            // Retrieves a task from the queue
            task = std::move(tasks.front());
            tasks.pop();
        }

        // Executes the task
        task();
    }
}

// Enqueues a task for execution
void parallel_scheduler::run(Task task) {
    {
        std::unique_lock<std::mutex> lock(mutex);
        tasks.emplace(std::move(task));
    }
    // Notifies one waiting thread to execute the task
    condVar.notify_one();
}
