#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 100

int main(int argc, char** argv){

    if(argc < 2){
        std::cerr << "FilePath isn't passed" << std::endl;
        exit(1);
    }
    //argument check

    char* first_File = argv[1];
    int open_First = open(first_File, O_WRONLY);
    if(open_First < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //file opening check

    char buffer[BUFFER_SIZE];
    for(int i = 0 ; i < BUFFER_SIZE ; i++ ){
        buffer[i] = '\0';
    }
    // buffer array elements attributed to '0'

    struct stat statBuf;
    int obt_Information = stat(first_File, &statBuf);
    if(obt_Information < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    // function shall obtain information about the named file and write it to the are pointed to by the buf argument.

    int file_Size = statBuf.st_size;
    //statBuf bytes size

    int written_Bytes = 0;
    int count = 0;
    while(count < file_Size){
        written_Bytes = write(open_First, buffer, BUFFER_SIZE);
        if(written_Bytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        count = count + written_Bytes;
    }
    //write 0's in file


    int remove = unlink(first_File);
    if(remove < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    // remove first_File from the system

}