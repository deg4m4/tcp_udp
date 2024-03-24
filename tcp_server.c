#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

#define SA struct sockaddr

void readWrite(int conn_fd)
{
    char buffer[MAX_BUFFER_SIZE];

    while (1)
    {
        bzero(buffer, sizeof(buffer));
        read(conn_fd, buffer, sizeof(buffer));
        printf("Client [%d]: %s", conn_fd, buffer);
        bzero(buffer, sizeof(buffer));

        
        write(conn_fd, buffer, sizeof(buffer));

        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    int sock_fd, conn_fd;
    struct sockaddr_in server_addr, client_addr;

    int len;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    int conn_ac = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (conn_ac < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int listen_ac = listen(sock_fd, 5);
    if (listen_ac < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    int pid;

    while (1)
    {

        int conn_fd = accept(sock_fd, (SA *)&client_addr, &len);
        if (conn_fd < 0)
        {
            printf("server accept failed...\n");
            exit(0);
        }
        else
        {
            printf("server accept the client [%d] ...\n", conn_fd);
        }

        if ((pid = fork()) == 0)
        {
            readWrite(conn_fd);
            close(conn_fd);
        }
    }

    // printf("Hello, World!\n");

    close(sock_fd);

    return 0;
}
