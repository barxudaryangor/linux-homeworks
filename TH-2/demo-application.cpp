#include <iostream>
#include "parralel_scheduler.h"
#include <mutex>
#include <functional>

std::mutex coutMutex;  // Mutex for synchronizing std::cout

void task1() {
    std::unique_lock<std::mutex> lock(coutMutex);
    std::cout << "Task 1 executed by thread " << std::this_thread::get_id() << std::endl;
}

void task2() {
    std::unique_lock<std::mutex> lock(coutMutex);
    std::cout << "Task 2 executed by thread " << std::this_thread::get_id() << std::endl;
}

void task3() {
    std::unique_lock<std::mutex> lock(coutMutex);
    std::cout << "Task 3 executed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    parallel_scheduler scheduler(3);

    // Enqueues tasks for execution
    for (int i = 0; i < 5; ++i) {
        scheduler.run(task1);
        scheduler.run(task2);
        scheduler.run(task3);
    }

    return 0;
}