// user_handler.c
#include "user_handler.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define USER_FILE "user_data.txt"

// Hash a password with SHA-1
void hash_password(const char *password, char *hash_output) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)password, strlen(password), hash);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&hash_output[i * 2], "%02x", hash[i]);
    }
}

// Register a new user
int register_user(const char *username, const char *email, const char *password) {
    char hashed_password[SHA_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    FILE *file = fopen(USER_FILE, "a+");
    if (file == NULL) {
        perror("Could not open user file");
        return -1;
    }

    fprintf(file, "%s,%s,%s\n", username, email, hashed_password);
    fclose(file);
    return 0;
}

// Authenticate user login
int authenticate_user(const char *username, const char *password) {
    char hashed_password[SHA_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        perror("Could not open user file");
        return -1;
    }

    char line[256], file_username[50], file_email[50], file_password[SHA_DIGEST_LENGTH * 2 + 1];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%s", file_username, file_email, file_password);
        if (strcmp(username, file_username) == 0 && strcmp(hashed_password, file_password) == 0) {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication failed
}
