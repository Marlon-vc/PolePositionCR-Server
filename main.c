#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main() {
    int server_fd, new_socket, val_read;
    struct sockaddr_in address;
    int opt = 1;
    int addr_len = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server!";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Failed to set socket options");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Failed to bind socket");
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Failed to listen");
        return -1;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addr_len)) < 0) {
        perror("Error accepting connection");
        return -1;
    }

    val_read = read(new_socket, buffer, 1024);

    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Message sent!\n");

    return 0;
}
