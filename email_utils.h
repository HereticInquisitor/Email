#ifndef EMAIL_UTILS_H
#define EMAIL_UTILS_H

#include <time.h>

struct Email {
    char sender[50];
    char recipient[50];
    char subject[100];
    char message[1024];
    time_t timestamp; // Ensure the timestamp is included
};

// Function prototypes
int store_email(struct Email *email); // Store email and return int

#endif
