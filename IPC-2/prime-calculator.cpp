#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <string.h>

// Function to find the nth prime number
int mTH_prime(int num) 
{
    int PrimeCount = 0;
    int i, flag, prime = 1;
    while (num != PrimeCount)
    {
        flag = 0;
        prime++;
        for (i = 2; i <= (prime / 2); i++)
        {
            if (prime % i == 0)
                flag = 1;
        }
        if (flag == 0)
        {
            PrimeCount++;
        }
    }

    return prime;
}

int main()
{
    // Pipe file descriptors for communication between parent and child processes
    int pipefd_1[2];
    int pipefd_2[2];

    // Create pipes and check for errors
    int pipe_result_1 = pipe(pipefd_1);
    if (pipe_result_1 < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int pipe_result_2 = pipe(pipefd_2);
    if (pipe_result_2 < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Fork to create a child process
    int pid = fork();

    if (pid < 0)
    {
        std::cerr << strerror(errno) << "No child process is created" << std::endl;
        exit(errno);
    }

    if (pid == 0) // child process
    {
        // Close unnecessary pipe ends
        close(pipefd_1[1]);
        close(pipefd_2[0]);

        int m;

        while (true)
        {
            // Read input from the parent process
            int rd_res = read(pipefd_1[0], &m, sizeof(m));

            if (rd_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            // Calculate the mth prime number
            int result = mTH_prime(m);

            // Send the result back to the parent process
            int wr_res = write(pipefd_2[1], &result, sizeof(result));

            if (wr_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }
        }
    }

    if (pid > 0) // parent process
    {
        // Close unnecessary pipe ends
        close(pipefd_1[0]);
        close(pipefd_2[1]);

        while (true)
        {
            std::string input;
            std::cout << "Please enter the number or 'exit' " << std::endl;
            std::cin >> input;

            // Check if the user wants to exit
            if (input == "exit")
            {
                std::cout << "Exiting" << std::endl;
                break;
            }

            int m;

            // Convert the input string to an integer
            m = std::stoi(input);

            // Send the input to the child process
            int wr_res = write(pipefd_1[1], &m, sizeof(m));
            if (wr_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            int result;

            // Receive the result from the child process
            int rd_res = read(pipefd_2[0], &result, sizeof(result));
            if (rd_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            // Display the result
            std::cout << "Received calculation result of prime(" << m << ") = " << result << std::endl;
        }
    }
}
