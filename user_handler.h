// user_handler.h
#ifndef USER_HANDLER_H
#define USER_HANDLER_H

void hash_password(const char *password, char *hash_output);
int register_user(const char *username, const char *email, const char *password);
int authenticate_user(const char *username, const char *password);

#endif
