#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/auth.h"
#include "../include/transaction.h"
#include "../include/budget.h"
#include "../include/analytics.h"
#include "../include/forecast.h"
#include "../include/file_io.h"

// Month selection function
void selectMonth(char *selectedMonth) {
    printf("\n    📅 SELECT MONTH (2025)\n");
    printf("    =====================\n\n");
    printf("    Available months: 2025-01 to 2025-07\n");
    printf("    Enter month (YYYY-MM): ");
    scanf("%s", selectedMonth);
    printf("\n    📊 Displaying data for: %s\n", selectedMonth);
}

void displayMainMenu(const char *username) {
    clearScreen();
    printHeader("🏠 MAIN MENU");
    printf("    👋 Welcome, %s!\n\n", username);
    printf("    📊 Your Financial Dashboard:\n\n");
    printf("    1. 💰 Add Transaction\n");
    printf("    2. 📋 View Monthly Transactions\n");
    printf("    3. 🎯 Set Budget\n");
    printf("    4. 📈 Check Budget Status\n");
    printf("    5. 📊 Monthly Analytics\n");
    printf("    6. 📄 Generate Monthly Report\n");
    printf("    7. 🔮 Expense Forecast\n");
    printf("    8. 💵 Check Balance\n");
    printf("    9. 🚪 Logout\n\n");
    printf("    Choose an option: ");
}

void displayAuthMenu() {
    clearScreen();
    displayWelcomeScreen();
    printf("    1. 🔐 Login to Existing Account\n");
    printf("    2. 👥 Use Pre-loaded User\n");
    printf("    3. 📝 Register New Account\n");
    printf("    4. ❌ Exit Application\n\n");
    printf("    Choose an option: ");
}

void debugCheckCurrentUser(const char *username) {
    printf("\n=== DEBUG: CURRENT USER DATA ===\n");
    printf("Current user: '%s'\n", username);
    
    // Check transactions for current user
    Transaction transaction;
    FILE *file = fopen("transactions.dat", "rb");
    int count = 0;
    
    if(file) {
        while(fread(&transaction, sizeof(Transaction), 1, file)) {
            if(strcmp(transaction.user, username) == 0) {
                count++;
                if(count <= 5) { 
                    printf("Found: %s | $%.2f | %s\n", 
                           transaction.type, transaction.amount, transaction.date);
                }
            }
        }
        fclose(file);
    }
    
    printf("Total transactions found: %d\n", count);
    printf("=== END DEBUG ===\n");
}

int main() {
    initializeFiles();
    createSampleUsers();
    initializeSampleData();
    
    char currentUser[MAX_USERNAME] = "";
    char selectedMonth[8] = "2025-01"; // Default month
    int choice;
    
    while(1) {
        if(strcmp(currentUser, "") == 0) {
            displayAuthMenu();
            scanf("%d", &choice);
            
            switch(choice) {
                case 1:
                    loginUser(currentUser);
                    break;
                case 2:
                    selectUser(currentUser);
                    break;
                case 3:
                    registerUser();
                    break;
                case 4:
                    printf("\n    👋 Thank you for using Finance Tracker! Goodbye! 👋\n\n");
                    return 0;
                default:
                    printf("\n    ❌ Invalid choice! Please try again.\n");
                    printf("    Press Enter to continue...");
                    getchar(); getchar();
            }
        } else {
            displayMainMenu(currentUser);
            scanf("%d", &choice);
            
            switch(choice) {
                case 1:
                    addTransaction(currentUser);
                    break;
                case 2:
                    selectMonth(selectedMonth);
                    viewMonthlyTransactions(currentUser, selectedMonth);
                    break;
                case 3:
                    setBudget(currentUser);
                    break;
                case 4:
                    selectMonth(selectedMonth);
                    checkBudgetStatus(currentUser, selectedMonth);
                    break;
                case 5:
                    selectMonth(selectedMonth);
                    showMonthlyAnalytics(currentUser, selectedMonth);
                    break;
                case 6:
                    selectMonth(selectedMonth);
                    generateMonthlyReport(currentUser, selectedMonth);
                    break;
                case 7:
                    printf("\n    Next month's predicted expense: $%.2f\n", predictNextMonthExpense(currentUser));
                    printf("    Press Enter to continue...");
                    getchar(); getchar();
                    break;
                case 8:
                    printf("\n    Current balance: $%.2f\n", getBalance(currentUser));
                    printf("    Press Enter to continue...");
                    getchar(); getchar();
                    break;
                case 9:
                    strcpy(currentUser, "");
                    printf("\n    ✅ Logged out successfully! See you soon! 👋\n");
                    printf("    Press Enter to continue...");
                    getchar(); getchar();
                    break;
                default:
                    printf("\n    ❌ Invalid choice! Please try again.\n");
                    printf("    Press Enter to continue...");
                    getchar(); getchar();
            }
        }
    }
    return 0;
}