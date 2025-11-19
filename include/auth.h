#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define USERS_FILE "users.dat"

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

// Function declarations
void displayWelcomeScreen();
void displayLoginScreen();
void displayRegisterScreen();
void clearScreen();
void printHeader(const char* title);
int registerUser();
int loginUser(char *currentUser);
int userExists(const char *username);

#endif