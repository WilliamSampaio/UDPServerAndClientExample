// Client side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    std::cout << "::: CLIENT :::\n";
    while (true)
    {
        std::string message;

        std::cout << "::: ";
        std::cin >> message;

        sendto(
            sockfd,
            (const char *)message.c_str(),
            strlen(message.c_str()),
            MSG_CONFIRM,
            (const struct sockaddr *)&servaddr,
            sizeof(servaddr));

        std::cout << "Esperando resposta...\n";
        n = recvfrom(
            sockfd,
            (char *)buffer,
            MAXLINE,
            MSG_WAITALL,
            (struct sockaddr *)&servaddr,
            &len);

        buffer[n] = '\0';
        std::cout << "(SERVER): " << buffer << '\n';
    }

    close(sockfd);
    return 0;
}