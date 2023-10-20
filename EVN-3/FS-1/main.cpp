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


    char* filepath_Read = argv[1];

    int file_Open = open(filepath_Read, O_RDONLY);
    if(file_Open < 0)
    {
        std::cerr << strerror(errno) << std::endl;    
    }
    //file opening 


    char buffer[BUFFER_SIZE];

    while(true){
        ssize_t readed_Bytes = read(file_Open, buffer, BUFFER_SIZE);

        if(readed_Bytes < 0)
        {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
        }

        if(readed_Bytes == 0){
            break;
        }

        buffer[readed_Bytes] = '\0';
        std::cout << buffer;
    }
    // reading file, and printing buf


    int close_Result = close(file_Open);
    if(close_Result < 0){
        std:: cerr << strerror(errno) << std::endl;
    }
    // file closing

    return 0;
}
