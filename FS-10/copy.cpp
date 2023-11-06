#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 222


int main(int argc, char** argv){

    if(argc < 3){
        std::cerr << "File Path isn't given" << std::endl;
        exit(1);
    }

    char* src_file = argv[1];
    char* dest_file = argv[2];

    int src_fd = open(src_file, O_RDONLY);

    if(src_fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(dest_fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    

    char buf[BUFFER_SIZE];

    while(true){
        ssize_t read_bytes = read(src_fd , buf , BUFFER_SIZE);

        if(read_bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        if(read_bytes == 0){
            break;
        }

        ssize_t write_bytes = write(dest_fd , buf , read_bytes);
        if(write_bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    
    int dt_bytes_count = 0;
    int hl_bytes_count = 0;
    int hole_bytes = 0;
    int data_bytes = 0;

    int offset = lseek(dest_fd , 0 , SEEK_SET);

    if(offset < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int file_end = lseek(dest_fd , 0 , SEEK_END);

    if(file_end < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    while(offset < file_end){
        hole_bytes = lseek(dest_fd, offset , SEEK_DATA);

        if(hole_bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
            break;
        }

        data_bytes = lseek(dest_fd, offset, SEEK_HOLE);

        if(data_bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
            break;
        }

        

        dt_bytes_count += data_bytes;
        hl_bytes_count += hole_bytes;

        offset = lseek(dest_fd, BUFFER_SIZE, SEEK_CUR);
        if(offset < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
            break;
        }
    }

    int total_bytes = dt_bytes_count + hl_bytes_count;

    int closed = close(src_fd);

    if(closed < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    
    closed = close(dest_fd);

    if(closed < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    std::cout << "Successfully copied " <<  total_bytes << " bytes (data: " << dt_bytes_count << ", hole: " << hl_bytes_count << ") " << std::endl;

    return 0;

    





}