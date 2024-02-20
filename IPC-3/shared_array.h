#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
#include <mutex>
#include <condition_variable>

#define pg_size 4096

class shared_array
{
private:
    std::string name;
    int size;
    sem_t* sem;
    int* ptr;
    int count = 1;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    shared_array(std::string name, int size);
    int& operator[](int index);
    ~shared_array();
    
};

#endif