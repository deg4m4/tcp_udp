#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);

    char buffer[100];
    char *message = "Hello Client";
    int listenfd, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;

    int bind_ac = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (bind_ac < 0)
    {
        perror("bind failed");
        return 1;
    }

    while (1)
    {
        bzero(buffer, sizeof(buffer));

        len = sizeof(cliaddr);
        int n = recvfrom(listenfd, buffer, 100,
                         0, (struct sockaddr *)&cliaddr, &len); // receive message from server
        buffer[n] = '\0';
        puts(buffer);
    }

    return 0;
}