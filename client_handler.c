#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "email_utils.h"

void *handle_client(void *arg) {
    int sock = *(int *)arg;
    free(arg); // Free the allocated memory for client socket
    struct Email email;

    while (recv(sock, &email, sizeof(email), 0) > 0) {
        email.timestamp = time(NULL); // Set the current timestamp
        
        // Store the email and check the return value
        if (store_email(&email) == 0) {
            send(sock, "ACK", 3, 0);
        } else {
            perror("Failed to store email");
        }
    }

    close(sock);
    return NULL;
}
