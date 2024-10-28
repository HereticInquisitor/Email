// email_handler.c
#include "email_handler.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

#define EMAIL_FILE "email_data.txt"

// Store an email
int store_email(struct Email *email) {
    FILE *file = fopen(EMAIL_FILE, "a+");
    if (file == NULL) {
        perror("Could not open email file");
        return -1;
    }
    fprintf(file, "%s,%s,%ld,%s,%s\n", email->sender, email->recipient, email->timestamp, email->subject, email->body);
    fclose(file);
    return 0;
}
