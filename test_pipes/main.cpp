#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "wait.h"
#include "socket_functions.h"

int main() {
    int sockfd[2];
    char buffer[4096];

    // Create socket pair
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) == -1) {
        perror("Socket pair creation failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process (Program B)

        // Redirect stdin, stdout, and stderr to socket
        dup2(sockfd[0], STDIN_FILENO);
        dup2(sockfd[0], STDOUT_FILENO);
        dup2(sockfd[0], STDERR_FILENO);

        // Close unused socket end
        close(sockfd[1]);

        // Execute Program B (replace "programB" with the actual command)
        execlp("/bin/bash", "/bin/bash", NULL);

        // If execlp fails
        perror("Program B execution failed");
        _exit(1);
    } else {
        // Parent process (Program A)

        // Close unused socket end
        close(sockfd[0]);

        while (true) {
            // Get user input for the command
            std::string userInput;
            std::cout << "Enter command: ";
            std::getline(std::cin, userInput);
            userInput += "\n";  // Add newline to simulate pressing Enter

            // Send the command to Program B via the socket
            write(sockfd[1], userInput.c_str(), userInput.size());

            // Wait for the output from Program B
            ssize_t bytesRead = cat(sockfd[1], buffer, sizeof(buffer));
            if (bytesRead <= 0) {
                // If read returns 0 or negative value, it indicates EOF or an error.
                break;
            }
            std::cout.write(buffer, bytesRead);
        }

        // Close the socket
        close(sockfd[1]);

        // Wait for the child process to finish
        waitpid(pid, NULL, 0);
    }

    return 0;
}
