#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/ucontext.h>
#include <sys/types.h>
#include <pwd.h>

void get_signal(int sig, siginfo_t *info, void *ucontext) 
{
    
    pid_t sender_pid = info->si_pid;
    uid_t sender_uid = info->si_uid;
    struct passwd *pw = getpwuid(sender_uid);
    const char *sender_username =  pw->pw_name;

    ucontext_t *context = (ucontext_t *)ucontext;
    unsigned long eip = context->uc_mcontext.gregs[REG_RIP];
    unsigned long eax = context->uc_mcontext.gregs[REG_RAX];
    unsigned long ebx = context->uc_mcontext.gregs[REG_RBX];


    std::cout << "Received a SIGUSR1 signal from process " << sender_pid 
    << " executed by " << sender_uid << " (" << sender_username << ")." 
    << std::endl;
    std::cout << "State of the context: EIP = " << eip << ", EAX = " 
    << eax << ", EBX = " << ebx << "." << std::endl;
}

int main() 
{

    std::cout << "PID: " << getpid() << std::endl;
    
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = get_signal;

    int sig_result = sigaction(SIGUSR1, &action, NULL);

    if (sig_result < 0) 
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    

    while (true) 
    {
        sleep(1);
    }

    return 0;
}