#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include "../exception/exception.h"
#include "../account/account.h"
#define BUFFER_SIZE 1024
#define PORT 8080

void func(int connect_fd)
{
    return;
}

// Driver function
int main(int argc, char *argv[])
{
    // Catch wrong input
    if (argc != 2)
    {
        printf("Error: Please input port number\n");
        return 0;
    }

    char *port_number = argv[1];
    int port = atoi(port_number);
    int socket_fd, connect_fd, client_address_size;
    struct sockaddr_in server_address, client_address;

    if (port < 1 || port > 65535) {
		printf("Error: Invalid port\n");
		return 0;
	}

    // socket create and verification
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        printf("Error: Socket creation failed\n");
        exit(0);
    }
    else
        printf("Socket successfully created\n");
    bzero(&server_address, sizeof(server_address));

    // assign IP, PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
    if ((bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))) != 0)
    {
        printf("Error: Socket bind failed\n");
        exit(0);
    }
    else
        printf("Socket successfully bind\n");

    // Now server is ready to listen and verification
    if ((listen(socket_fd, 5)) != 0)
    {
        printf("Error: Listen failed\n");
        exit(0);
    }
    else
        printf("Server listening...\n");
    client_address_size = sizeof(client_address);

    // Accept the data packet from client_address and verification
    connect_fd = accept(socket_fd, (struct sockaddr *)&client_address, &client_address_size);
    if (connect_fd < 0)
    {
        printf("Error: Server accept failed\n");
        exit(0);
    }
    else
        printf("Server accept the client_address\n");

    // Function for chatting between client_address and server
    func(connect_fd);

    // After chatting close the socket
    printf("Server is closing...\n");
    close(socket_fd);
    printf("Server's closed\n");
}
