#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "FilePath isn't given";
        exit(1);
    }
    //argument check

    std::string s1 = "first line\n";
    std::string s2 = "second line\n";

    
    char* first_File = argv[1];
    int open_File = open(first_File, O_WRONLY);
    if(open_File < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //open first_File and check

    int duplicate_firstFile = dup(open_File);
    if(duplicate_firstFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //duplicate first_File and check

    int write_FirstLine = write(open_File, s1.c_str(), s1.size());
    if(write_FirstLine < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //write s1 in open_File and check

    int write_SecondLine = write(duplicate_firstFile, s2.c_str(), s2.size());
    if(write_SecondLine < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //write s2 in duplicated file and check

    int close_Original = close(open_File);
    if(close_Original < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //close Original file and check

    int close_Duplicat = close(duplicate_firstFile);
    if(close_Duplicat < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //close Duplicat file and check

    return 0;
}