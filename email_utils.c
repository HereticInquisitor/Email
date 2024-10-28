#include "email_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int store_email(struct Email *email) { // Change void to int
    FILE *file = fopen("emails.txt", "a");
    if (!file) {
        perror("Failed to open file");
        return -1; // Indicate failure
    }
    
    fprintf(file, "%s,%s,%s,%s,%ld\n", email->sender, email->recipient,
            email->subject, email->message, email->timestamp);
    fclose(file);
    
    return 0; // Indicate success
}
