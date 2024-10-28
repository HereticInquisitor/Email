// email_handler.h
#ifndef EMAIL_HANDLER_H
#define EMAIL_HANDLER_H

#include <time.h>

struct Email {
    char sender[50];
    char recipient[50];
    char subject[100];
    char body[1024];
    time_t timestamp;
};

int store_email(struct Email *email);

#endif
