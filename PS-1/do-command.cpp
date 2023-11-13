#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <string.h>
using namespace std;


void do_command(char** argv){
    struct tms start,end;

    time_t start_time, end_time;

    start_time = times(&start);

    pid_t pid = fork();

    if(pid < 0){
        cout << "Something was failed" << endl;
        exit(1);
    }

    if(pid == 0){
        int result = execvp(argv[0], argv);
        if(result < 0){
            cout << strerror(errno) << endl;
            exit(errno);
        }
    }

    else{
        int status;

        int waitPid = waitpid(pid,&status,0);
        end_time = times(&end);

        double timing = (double) (end_time - start_time);

        cout << "Command completed with " << status << " " << "exit code and took " << timing << " " << "seconds." << endl;

    }

}

int main (int argc, char** argv){
    if(argc < 2){
        std::cerr << "Command not provided";
        exit(1);
    }

    do_command(argv+1);
}
