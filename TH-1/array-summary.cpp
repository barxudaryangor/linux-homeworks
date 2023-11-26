#include <iostream>
#include <cstdlib>
#include <errno.h>
#include <vector>
#include <ctime>
#include <string.h>
#include <chrono>
#include <pthread.h>

// Structure to store thread-specific information
struct ThreadInfo {
    int start;             
    int end;               
    long long sum_of_threads;  
};

// Function executed by each thread to calculate the sum within its designated range
void* ThreadSum(void* threadArg) {
    ThreadInfo* info = static_cast<ThreadInfo*>(threadArg);
    info->sum_of_threads = 0;

    for(auto i = info->start ; i != info->end ; i++) {
        info->sum_of_threads += i;
    }
    return NULL;
}

int main(int argc, char** argv) {
    // Check if the required command-line arguments are provided
    if(argc < 3) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //Change command-line args to int
    int N = std::atoi(argv[1]);  
    int M = std::atoi(argv[2]);  

    // Generate an array of random numbers
    std::vector<int> arr(N);
    for(int i = 0 ; i < N ; i++) {
        arr[i] = rand();
    }

    // Measure time without using threads
    std::clock_t start_time = std::clock();

    // Calculate the sum of the array without using threads
    long long sum = 0;
    for(int i = 0 ; i < N ; i++) {
        sum += arr[i];
    }

    // Measure and print the time spent without using threads
    std::clock_t end_time = std::clock();
    double duration = static_cast<double>(end_time - start_time);
    std::cout << "Time spent without threads " << duration << " microseconds" << std::endl;

    // Reset sum for the next calculation
    sum = 0;

    // Data structures to manage thread information and pthreads
    std::vector<ThreadInfo> thread_data(M);
    std::vector<pthread_t> threads(M);

    // Measure time with threads
    start_time = std::clock();
    int current_index = 0;
    
    // Create threads and assign each thread a range of indices to calculate the sum
    for(int i = 0 ; i < M ; i++) {

        thread_data[i] = {current_index, current_index + (i < (N % M) ? N / M + 1 : N / M)};

        // Create a new thread
        int pthread_create_result = pthread_create(&threads[i], NULL, ThreadSum, &thread_data[i]);
        if(pthread_create_result < 0) {
            std::cerr << strerror(pthread_create_result) << std::endl;
            exit(pthread_create_result);
        }
        current_index = thread_data[i].end;
    }

    // Wait for threads finishing
    for(int i = 0 ; i < M ; i++) {
        int pthread_join_result = pthread_join(threads[i], NULL);
        if(pthread_join_result < 0) {
            std::cerr << strerror(pthread_join_result) << std::endl;
            exit(pthread_join_result);
        }
    }

    // Combine the computed sums of for each thread
    for(int i = 0 ; i < M ; i++) {
        sum += thread_data[i].sum_of_threads;
    }

    // The time spent with threads
    end_time = std::clock();
    duration = static_cast<double>(end_time - start_time);
    std::cout << "Time spent with threads " << duration << " microseconds" << std::endl;

    return 0;
}