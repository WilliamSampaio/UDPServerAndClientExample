// Server side implementation of UDP client-server model
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
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len;
    int n;

    len = sizeof(cliaddr); // len is value/result

    std::cout << "::: SERVER :::\n";
    while (true)
    {
        std::cout << "Esperando resposta...\n";
        n = recvfrom(
            sockfd,
            (char *)buffer,
            MAXLINE,
            MSG_WAITALL,
            (struct sockaddr *)&cliaddr,
            &len);

        buffer[n] = '\0';

        printf("(CLIENT): %s\n", buffer);

        std::string message;

        std::cout << "::: ";
        std::cin >> message;

        sendto(
            sockfd,
            (const char *)message.c_str(),
            strlen(message.c_str()),
            MSG_CONFIRM,
            (const struct sockaddr *)&cliaddr,
            sizeof(cliaddr));
    }
    return 0;
}