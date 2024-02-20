#include "shared_array.h"
#include <iostream>
#include <semaphore.h>

int main()
{
    sem_t* sem = sem_open("example", O_CREAT, 0666, 1);
    if(sem == SEM_FAILED)
    {
        std::cerr << "Semaphore fail" << strerror(errno) << std::endl;
        exit(errno);
    }

    shared_array array("example_array", 10);
    while(true)
    {
        sem_wait(sem);
        for(int i = 0 ; i < 10 ; i++)
        {
            std::cout << "Second process: array[" << i << "] = " << array[i] << std::endl;
        }
        sem_post(sem);
        sleep(1);
    }
    sem_close(sem);
    sem_unlink("example");
    return 0; 
}