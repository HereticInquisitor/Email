// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void send_email(int sock) {
    char recipient[50], subject[100], body[1024];
    printf("Enter recipient: ");
    scanf("%s", recipient);
    printf("Enter subject: ");
    scanf("%s", subject);
    printf("Enter body: ");
    scanf("%s", body);

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "SEND|my_username|%s|%s|%s", recipient, subject, body);
    send(sock, buffer, strlen(buffer), 0);
}
