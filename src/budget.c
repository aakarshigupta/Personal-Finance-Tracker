#include <stdio.h>
#include <string.h>
#include "../include/budget.h"
#include "../include/transaction.h"

void setBudget(const char *username) {
    Budget budget;
    FILE *file = fopen(BUDGET_FILE, "ab");
    
    printf("\n    🎯 SET BUDGET\n");
    printf("    ============\n\n");
    
    printf("    Category: ");
    scanf("%s", budget.category);
    printf("    Monthly Budget Limit: $");
    scanf("%f", &budget.limit);
    strcpy(budget.user, username);
    
    if(file) {
        fwrite(&budget, sizeof(Budget), 1, file);
        fclose(file);
        printf("\n    ✅ Budget set for %s: $%.2f\n", budget.category, budget.limit);
    } else {
        printf("\n    ❌ Error setting budget!\n");
    }
    
    printf("    Press Enter to continue...");
    getchar(); getchar();
}

void checkBudget(const char *username) {
    Budget budget;
    FILE *budgetFile = fopen(BUDGET_FILE, "rb");
    Transaction transaction;
    FILE *transFile = fopen(TRANSACTIONS_FILE, "rb");
    
    printf("\n    📈 BUDGET STATUS\n");
    printf("    ===============\n\n");
    
    int found = 0;
    
    if(budgetFile) {
        while(fread(&budget, sizeof(Budget), 1, budgetFile)) {
            if(strcmp(budget.user, username) == 0) {
                found = 1;
                float spent = 0;
                
                // Calculate spending in this category
                if(transFile) {
                    fseek(transFile, 0, SEEK_SET);
                    while(fread(&transaction, sizeof(Transaction), 1, transFile)) {
                        if(strcmp(transaction.user, username) == 0 &&
                           strcmp(transaction.category, budget.category) == 0 &&
                           strcmp(transaction.type, "expense") == 0) {
                            spent += transaction.amount;
                        }
                    }
                }
                
                float remaining = budget.limit - spent;
                float usagePercent = (spent / budget.limit) * 100;
                
                printf("    Category: %s\n", budget.category);
                printf("    Budget: $%.2f | Spent: $%.2f | Remaining: $%.2f\n", 
                       budget.limit, spent, remaining);
                printf("    Usage: %.1f%%", usagePercent);
                
                if(usagePercent >= 90) {
                    printf(" 🚨 OVER BUDGET!\n");
                } else if(usagePercent >= 75) {
                    printf(" ⚠️  Close to limit\n");
                } else {
                    printf(" ✅ Within budget\n");
                }
                printf("    --------------------\n");
            }
        }
        fclose(budgetFile);
    }
    
    if(transFile) fclose(transFile);
    
    if(!found) {
        printf("    No budgets set. Use 'Set Budget' first.\n");
    }
    
    printf("\n    Press Enter to continue...");
    getchar(); getchar();
}