#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 9000

void *handle_client(void *arg); // Forward declaration

int setup_server_socket(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

int main() {
    int server_fd = setup_server_socket(PORT);
    printf("Server is running on port %d\n", PORT);

    while (1) {
        int *new_socket = malloc(sizeof(int)); // Allocate memory for the new socket
        *new_socket = accept(server_fd, (struct sockaddr *)NULL, NULL);
        if (*new_socket < 0) {
            perror("Accept failed");
            free(new_socket); // Free allocated memory
            continue;
        }
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, new_socket);
        pthread_detach(thread_id); // Detach the thread
    }

    return 0;
}
