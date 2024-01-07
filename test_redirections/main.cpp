//
// Created by sofiiafolv on 1/7/24.
//

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket_functions.h"
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "wait.h"

int main() {
    struct sockaddr_in server;
    char buf[1024];
    int sd, psd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "mydocker: failed to create socket" << std::endl;
    }
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(8000);
    int res = bind(sd, (struct sockaddr *) &server, sizeof(server));
    if (res == -1) {
        std::cerr << "mydocker: failed to bind socket" << std::endl;
    }
    listen(sd, 1);
    psd = accept(sd, nullptr, nullptr);
    close(sd);
//    for (;;) {
//        int cc = readn(psd, buf, sizeof(buf));
//        if (cc == 0) {
//            writen(psd, "closed", sizeof("closed"));
//            exit(EXIT_SUCCESS);
//        }
//        buf[cc] = '\0';
//    }
    int sockfd[2];
    char buffer[8];

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
        execlp("./bin/test_bin", "./bin/test_bin", NULL);
//        execlp("/bin/bash", "/bin/bash","-i",NULL);

        // If execlp fails
        perror("Program B execution failed");
        _exit(1);
    } else {
        // Parent process (Program A)

        // Close unused socket end
        close(sockfd[0]);
        int flags = fcntl(sockfd[1], F_GETFL, 0);
        if (flags == -1) {
            perror("fcntl");
            return EXIT_FAILURE;
        }
        flags |= O_NONBLOCK;  // Set the O_NONBLOCK flag
        if (fcntl(sockfd[1], F_SETFL, flags) == -1) {
            perror("fcntl");
            return EXIT_FAILURE;
        }
        while (true) {
            ssize_t bytesRead = cat(sockfd[1], buffer, sizeof(buffer), psd);
            std::string command(buffer, bytesRead);
            std::cout << command << std::endl;
            if (boost::algorithm::trim_copy(command) == "shutdown") {
                // Shutdown logic
                close(sockfd[1]);
                break;  // Exit the loop and close the socket
            }

            // Handle other commands if needed

//            if (bytesRead <= 0) {
//                // If read returns 0 or negative value, it indicates EOF or an error.
//                break;
//            }
//            // Get user input for the command
//            std::string userInput;
//            std::cout << "Enter command: ";
//            std::getline(std::cin, userInput);
//            userInput += "\n";  // Add newline to simulate pressing Enter
//
//            // Send the command to Program B via the socket
//            write(sockfd[1], userInput.c_str(), userInput.size());
//            std::cout.write(buffer, bytesRead);

        }

        // Close the socket
        close(sockfd[1]);

        // Wait for the child process to finish
        waitpid(pid, NULL, 0);
    }

    return 0;
}