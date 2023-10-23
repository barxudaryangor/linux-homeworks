#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void initialize(int argc, char** argv){
    if(argc < 2){
        std::cerr << "FilePath isn't passed" << std::endl;
        exit(1);
    }
    //argument check

    char* first_File = argv[1];
    int open_First = open(first_File, O_RDWR);
    if(open_First < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //first_file open with reading and writing priority

    int second_File = dup2(open_First,0);
    if(second_File < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    // new file for std::cin 

    int close_File = close(open_First);
    if(close_File < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //close file
}

int main(int argc, char** argv){

    initialize(argc,argv);
    // cin our text file

    std::string input;
    std::cin >> input;
    //create and read it

    int n = input.size();
    //geting our input's size

    std::string reversed = input;
    //create another string for reverse

    for(int i = 0 ; i < n / 2 ; i++){
        std::swap (reversed[i],  reversed[n-i-1]);
    }
    // swapping our string elements

    reversed[n+1] = '\0';
    //string end

    std::cout << reversed << std::endl ;
    //print our reversed string
    return 0;

}