#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "email_utils.h"

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    struct Email email;
    strcpy(email.sender, "sender@example.com");
    strcpy(email.recipient, "recipient@example.com");
    strcpy(email.subject, "Test Email");
    strcpy(email.message, "This is a test email.");

    send(sock, &email, sizeof(email), 0);
    char buffer[3];
    recv(sock, buffer, sizeof(buffer), 0); // Receive acknowledgment

    printf("Server Response: %s\n", buffer);

    close(sock);
    return 0;
}
