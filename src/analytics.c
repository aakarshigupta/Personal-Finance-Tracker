#include <stdio.h>
#include <string.h>
#include "../include/analytics.h"
#include "../include/transaction.h"
#include "../include/budget.h"

// View transactions for specific month
void viewMonthlyTransactions(const char *username, const char *month) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    int found = 0;
    float monthlyIncome = 0, monthlyExpense = 0;
    
    printf("\n    📋 TRANSACTIONS FOR %s\n", month);
    printf("    ========================\n\n");
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0 &&
               strncmp(transaction.date, month, 7) == 0) {
                printf("    %s | %s | $%.2f | %s\n", 
                       transaction.date, transaction.type, transaction.amount,
                       transaction.category);
                printf("    Description: %s\n", transaction.description);
                printf("    ------------------------------------\n");
                
                if(strcmp(transaction.type, "income") == 0) {
                    monthlyIncome += transaction.amount;
                } else {
                    monthlyExpense += transaction.amount;
                }
                found = 1;
            }
        }
        fclose(file);
    }
    
    if(!found) {
        printf("    📭 No transactions found for %s.\n", month);
    } else {
        printf("\n    📊 MONTHLY SUMMARY (%s):\n", month);
        printf("    Total Income:  $%.2f\n", monthlyIncome);
        printf("    Total Expense: $%.2f\n", monthlyExpense);
        printf("    Net Savings:   $%.2f\n", monthlyIncome - monthlyExpense);
    }
    
    printf("\n    Press Enter to continue...");
    getchar(); getchar();
}

// Show spending by category for specific month
void showMonthlyAnalytics(const char *username, const char *month) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    float categoryTotals[10] = {0};
    char categories[10][MAX_CATEGORY];
    int categoryCount = 0;
    
    printf("\n    📊 SPENDING ANALYTICS FOR %s\n", month);
    printf("    =============================\n\n");
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0 && 
               strcmp(transaction.type, "expense") == 0 &&
               strncmp(transaction.date, month, 7) == 0) {
                
                int found = 0;
                for(int i = 0; i < categoryCount; i++) {
                    if(strcmp(categories[i], transaction.category) == 0) {
                        categoryTotals[i] += transaction.amount;
                        found = 1;
                        break;
                    }
                }
                
                if(!found && categoryCount < 10) {
                    strcpy(categories[categoryCount], transaction.category);
                    categoryTotals[categoryCount] = transaction.amount;
                    categoryCount++;
                }
            }
        }
        fclose(file);
    }
    
    if(categoryCount == 0) {
        printf("    No expense data found for %s.\n", month);
    } else {
        printf("    Category-wise Spending:\n\n");
        for(int i = 0; i < categoryCount; i++) {
            printf("    %-15s: $%.2f\n", categories[i], categoryTotals[i]);
        }
        
        // Show spending chart
        printf("\n    📈 SPENDING CHART:\n");
        float totalExpense = 0;
        for(int i = 0; i < categoryCount; i++) {
            totalExpense += categoryTotals[i];
        }
        
        if(totalExpense > 0) {
            printf("    ");
            for(int i = 0; i < categoryCount; i++) {
                int bars = (int)((categoryTotals[i] / totalExpense) * 20);
                printf("%s: ", categories[i]);
                for(int j = 0; j < bars; j++) {
                    printf("█");
                }
                printf(" (%.1f%%)\n    ", (categoryTotals[i] / totalExpense) * 100);
            }
        }
    }
    
    printf("\n    Press Enter to continue...");
    getchar(); getchar();
}

// Generate monthly report
void generateMonthlyReport(const char *username, const char *month) {
    Transaction transaction;
    FILE *file = fopen(TRANSACTIONS_FILE, "rb");
    float totalIncome = 0, totalExpense = 0;
    
    printf("\n    📄 MONTHLY REPORT FOR %s\n", month);
    printf("    =========================\n\n");
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0 &&
               strncmp(transaction.date, month, 7) == 0) {
                
                if(strcmp(transaction.type, "income") == 0) {
                    totalIncome += transaction.amount;
                } else {
                    totalExpense += transaction.amount;
                }
            }
        }
        fclose(file);
    }
    
    printf("    📈 FINANCIAL SUMMARY\n");
    printf("    ====================\n");
    printf("    Total Income:    $%.2f\n", totalIncome);
    printf("    Total Expense:   $%.2f\n", totalExpense);
    printf("    --------------------\n");
    printf("    Net Savings:     $%.2f\n\n", totalIncome - totalExpense);
    
    if(totalIncome > 0) {
        float savingsRate = ((totalIncome - totalExpense) / totalIncome) * 100;
        printf("    💰 SAVINGS RATE: %.1f%%\n\n", savingsRate);
        
        if(savingsRate >= 20) {
            printf("    ✅ Excellent savings rate! Keep it up! 🎉\n");
        } else if(savingsRate >= 10) {
            printf("    ⚠️  Good savings rate. Room for improvement.\n");
        } else {
            printf("    🚨 Low savings rate. Consider reducing expenses.\n");
        }
    }
    
    printf("\n    Press Enter to continue...");
    getchar(); getchar();
}

// Check budget status for specific month
void checkBudgetStatus(const char *username, const char *month) {
    Budget budget;
    FILE *budgetFile = fopen(BUDGET_FILE, "rb");
    Transaction transaction;
    FILE *transFile = fopen(TRANSACTIONS_FILE, "rb");
    
    printf("\n    📈 BUDGET STATUS FOR %s\n", month);
    printf("    =======================\n\n");
    
    int found = 0;
    
    if(budgetFile) {
        while(fread(&budget, sizeof(Budget), 1, budgetFile)) {
            if(strcmp(budget.user, username) == 0) {
                found = 1;
                float spent = 0;
                
                // Calculate spending in this category for the month
                if(transFile) {
                    fseek(transFile, 0, SEEK_SET);
                    while(fread(&transaction, sizeof(Transaction), 1, transFile)) {
                        if(strcmp(transaction.user, username) == 0 &&
                           strcmp(transaction.category, budget.category) == 0 &&
                           strcmp(transaction.type, "expense") == 0 &&
                           strncmp(transaction.date, month, 7) == 0) {
                            spent += transaction.amount;
                        }
                    }
                }
                
                float remaining = budget.limit - spent;
                float usagePercent = (spent / budget.limit) * 100;
                
                printf("    📊 %s\n", budget.category);
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

// Original functions for compatibility
void showSpendingByCategory(const char *username) {
    showMonthlyAnalytics(username, "2025-01");
}

void generateMonthlyReportOld(const char *username) {
    generateMonthlyReport(username, "2025-01");
}

void displaySpendingChart(const char *username) {
    showMonthlyAnalytics(username, "2025-01");
}