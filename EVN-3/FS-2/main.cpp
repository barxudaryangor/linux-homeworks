#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 100

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "Filepath isn't passed." << std::endl;
        exit(1);
    }
    //argument check

    char* first_File = argv[1];
    int open_First = open(first_File, O_RDONLY);
    //open first_File 'readonly'

    if(open_First < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    

    char* second_File = argv[2];
    int open_Second = open(second_File, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
    //open second_file 

    if(open_Second < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buffer[BUFFER_SIZE];
    //creating buffer using given size with define method
    

    while(true){
        ssize_t readed_Bytes = read(open_First, buffer, BUFFER_SIZE);

        if(readed_Bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        } 

        if(readed_Bytes == 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        ssize_t written_Bytes = write(open_Second, buffer, readed_Bytes);

        if(written_Bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }
    // reading the source file, checking error while reading, writing newfile, checking error while writing


    int close_First = close(open_First);
    int close_Second = close(open_Second);

    if(close_First < 0){
        std:: cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    if(close_Second < 0){
        std:: cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    // closing the source and writing files, checking error while closing


    return 0;
}
