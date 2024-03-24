// https://www.geeksforgeeks.org/udp-client-server-using-connect-c-implementation/

// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE 1000

// Driver code
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    char buffer[100];
    char *message = "Hello Server";
    int sockfd, n;
    struct sockaddr_in servaddr;

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;

    // create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }

    while (1)
    {

        bzero(buffer, sizeof(buffer));
        n = 0;
        printf("Send to server: ");
        while ((buffer[n++] = getchar()) != '\n')
            ;
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, sizeof(servaddr));
            
    }

    // close the descriptor
    close(sockfd);
}
