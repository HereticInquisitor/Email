// server.c
#include "user_handler.h"
#include "email_handler.h"
#include "socket_utils.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *handle_client(void *client_socket) {
    int sock = *(int *)client_socket;
    char buffer[1024];

    // Handle client commands
    while (recv(sock, buffer, sizeof(buffer), 0) > 0) {
        if (strncmp(buffer, "SEND", 4) == 0) {
            // Extract email details and store email
            char sender[50], recipient[50], subject[100], body[1024];
            sscanf(buffer + 5, "%[^|]|%[^|]|%[^|]|%s", sender, recipient, subject, body);

            struct Email email;
            strcpy(email.sender, sender);
            strcpy(email.recipient, recipient);
            strcpy(email.subject, subject);
            strcpy(email.body, body);
            email.timestamp = time(NULL);

            if (store_email(&email) == 0) {
                send(sock, "ACK", 3, 0);
            } else {
                send(sock, "FAIL", 4, 0);
            }
        }
        memset(buffer, 0, sizeof(buffer));
    }

    close(sock);
    pthread_exit(NULL);
}

int main() {
    int server_fd = setup_server_socket(8080);
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (1) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *)&new_socket);
    }

    close(server_fd);
    return 0;
}
