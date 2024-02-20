#include "shared_array.h"
#include <cerrno>
#include <cstdlib>

    shared_array::shared_array(std::string name, int size) : size(size), name(name)
    {
        name = name + '_' + std::to_string(size);
        int fd = shm_open(name.c_str(), O_CREAT | O_RDWR , 0666);
        if(fd < 0)
        {
            std::cerr << "Opening failed: " << strerror(errno) << std::endl;
            exit(errno);
        }

        int length = size / pg_size;
        if(size % pg_size != 0)
        {
            length++;
        }
        length*= pg_size;

        if(ftruncate(fd, length) < 0)
        {
            std::cerr << "Creating failed: " << strerror(errno) << std::endl;
            close(fd);
            exit(errno);
        }

        

        void* map;
        map = mmap(NULL , length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        if(map == MAP_FAILED)
        {
            std::cerr << "Memory mapping failed: " << strerror(errno) << std::endl;
            exit(errno);
        }

        ptr = static_cast<int*>(map);

        close(fd);
    }

    shared_array::~shared_array()
    {
        munmap(ptr, size * sizeof(int));
        shm_unlink(name.c_str()); 
    }

    int& shared_array::operator[](int index)
    {
        return ptr[index];
    }

