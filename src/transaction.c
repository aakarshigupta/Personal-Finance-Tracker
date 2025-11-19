#include <stdio.h>
#include <string.h>
#include "../include/transaction.h"
#include "../include/file_io.h"

void addTransaction(const char *username) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "ab");
    
    if(!file) {
        printf("\n    ❌ Error opening transactions file!\n");
        printf("    Trying to create file...\n");
        file = fopen(TRANSACTIONS_FILE, "wb");
        if(!file) {
            printf("    ❌ STILL CANNOT CREATE FILE!\n");
            return;
        }
        fclose(file);
        file = fopen(TRANSACTIONS_FILE, "ab");
    }
    
    transaction.id = getNextTransactionId();
    strcpy(transaction.user, username);
    
    printf("\n    💰 ADD TRANSACTION\n");
    printf("    =================\n\n");
    
    printf("    Type (income/expense): ");
    scanf("%s", transaction.type);
    printf("    Amount: ");
    scanf("%f", &transaction.amount);
    printf("    Category: ");
    scanf("%s", transaction.category);
    printf("    Date (YYYY-MM-DD): ");
    scanf("%s", transaction.date);
    printf("    Description: ");
    scanf(" %[^\n]", transaction.description);
    
    fwrite(&transaction, sizeof(Transaction), 1, file);
    fclose(file);
    
    printf("\n    ✅ Transaction added successfully! ID: %d\n", transaction.id);
    
    // Debug: Immediately check if transaction was saved
    debugCheckTransactions(username);
    
    printf("    Press Enter to continue...");
    getchar(); getchar();
}

void viewTransactions(const char *username) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    int found = 0;
    float totalIncome = 0, totalExpense = 0;
    
    printf("\n    📋 YOUR TRANSACTIONS\n");
    printf("    ===================\n\n");
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0) {
                printf("    ID: %d | %s | $%.2f | %s | %s\n", 
                       transaction.id, transaction.type, transaction.amount,
                       transaction.category, transaction.date);
                printf("    Description: %s\n", transaction.description);
                printf("    ------------------------------------\n");
                
                if(strcmp(transaction.type, "income") == 0) {
                    totalIncome += transaction.amount;
                } else {
                    totalExpense += transaction.amount;
                }
                found = 1;
            }
        }
        fclose(file);
    }
    
    if(!found) {
        printf("    📭 No transactions found.\n");
    } else {
        printf("\n    📊 SUMMARY:\n");
        printf("    Total Income: $%.2f\n", totalIncome);
        printf("    Total Expense: $%.2f\n", totalExpense);
        printf("    Net Balance: $%.2f\n", totalIncome - totalExpense);
    }
    
    printf("\n    Press Enter to continue...");
    getchar(); getchar();
}

float getBalance(const char *username) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    float balance = 0;
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0) {
                if(strcmp(transaction.type, "income") == 0) {
                    balance += transaction.amount;
                } else {
                    balance -= transaction.amount;
                }
            }
        }
        fclose(file);
    }
    return balance;
}

// DEBUG FUNCTION: Check all transactions in file
void debugCheckTransactions(const char *username) {
    printf("\n    === DEBUG: CHECKING ALL TRANSACTIONS ===\n");
    
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    if(!file) {
        printf("    ❌ Cannot open file: %s\n", TRANSACTIONS_FILE);
        return;
    }
    
    int totalCount = 0;
    int userCount = 0;
    
    printf("    Checking file: %s\n", TRANSACTIONS_FILE);
    
    while(fread(&transaction, sizeof(Transaction), 1, file)) {
        totalCount++;
        printf("    Transaction %d:\n", totalCount);
        printf("      User: '%s'\n", transaction.user);
        printf("      Type: '%s'\n", transaction.type);
        printf("      Amount: $%.2f\n", transaction.amount);
        printf("      Date: '%s'\n", transaction.date);
        printf("      Category: '%s'\n", transaction.category);
        printf("      Description: '%s'\n", transaction.description);
        printf("      --------------------\n");
        
        if(strcmp(transaction.user, username) == 0) {
            userCount++;
        }
    }
    
    fclose(file);
    printf("    Total transactions in file: %d\n", totalCount);
    printf("    Transactions for user '%s': %d\n", username, userCount);
    printf("    === END DEBUG ===\n\n");
}


void addTestData(const char *username) {
    printf("\n    🧪 ADDING TEST DATA FOR %s\n", username);
    
    Transaction transactions[3] = {
        {1, "income", 3000.0f, "salary", "2025-01-15", "Monthly salary", ""},
        {2, "expense", 1000.0f, "rent", "2025-01-01", "Monthly rent", ""},
        {3, "expense", 200.0f, "food", "2025-01-10", "Groceries", ""}
    };
    
    FILE *file = fopen(TRANSACTIONS_FILE, "ab");
    if(!file) {
        printf("    ❌ Cannot open file for test data!\n");
        return;
    }
    
    for(int i = 0; i < 3; i++) {
        strcpy(transactions[i].user, username);
        fwrite(&transactions[i], sizeof(Transaction), 1, file);
        printf("    ✅ Added: %s - $%.2f - %s\n", 
               transactions[i].type, transactions[i].amount, transactions[i].date);
    }
    
    fclose(file);
    
    debugCheckTransactions(username);
}