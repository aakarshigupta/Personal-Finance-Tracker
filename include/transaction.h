#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "auth.h"

#define MAX_CATEGORY 30
#define MAX_DATE 11
#define MAX_DESCRIPTION 100
#define TRANSACTIONS_FILE "transactions.dat"

typedef struct {
    int id;
    char type[10]; // "income" or "expense"
    float amount;
    char category[MAX_CATEGORY];
    char date[MAX_DATE];
    char description[MAX_DESCRIPTION];
    char user[MAX_USERNAME];
} Transaction;

void addTransaction(const char *username);
void viewTransactions(const char *username);
float getBalance(const char *username);

#endif