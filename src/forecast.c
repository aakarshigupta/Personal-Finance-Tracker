#include <stdio.h>
#include <string.h>
#include "../include/forecast.h"
#include "../include/transaction.h"

float predictNextMonthExpense(const char *username) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    float monthlyExpenses[12] = {0};
    int monthCount = 0;
    float total = 0;
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0 &&
               strcmp(transaction.type, "expense") == 0) {
                
                int month;
                sscanf(transaction.date, "%*d-%d", &month);
                monthlyExpenses[month-1] += transaction.amount;
            }
        }
        fclose(file);
    }
    
    int validMonths = 0;
    for(int i = 0; i < 12; i++) {
        if(monthlyExpenses[i] > 0) {
            total += monthlyExpenses[i];
            validMonths++;
        }
    }
    
    float prediction = (validMonths > 0) ? total / validMonths : 500.0;
    
    printf("\n    🔮 EXPENSE FORECAST\n");
    printf("    ==================\n\n");
    printf("    Based on your spending history:\n");
    printf("    Next month's predicted expense: $%.2f\n", prediction);
    
    if(validMonths > 0) {
        printf("    (Average of %d months data)\n", validMonths);
    } else {
        printf("    (Using default estimate)\n");
    }
    
    return prediction;
}