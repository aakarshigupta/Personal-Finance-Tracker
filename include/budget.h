#ifndef BUDGET_H
#define BUDGET_H

#include "auth.h" 

#define MAX_CATEGORY 30
#define BUDGET_FILE "budgets.dat"

typedef struct {
    char category[MAX_CATEGORY];
    float limit;
    char user[MAX_USERNAME];
} Budget;

void setBudget(const char *username);
void checkBudget(const char *username);

#endif