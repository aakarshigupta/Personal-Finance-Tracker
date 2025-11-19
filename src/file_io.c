#include <stdio.h>
#include <string.h>
#include "../include/file_io.h"
#include "../include/transaction.h"
#include "../include/budget.h"

void initializeFiles() {
    FILE *file;
    
    // Create files if they don't exist
    file = fopen("users.dat", "ab");
    if(file) fclose(file);
    
    file = fopen("transactions.dat", "ab");
    if(file) fclose(file);
    
    file = fopen("budgets.dat", "ab");
    if(file) fclose(file);
}

int getNextTransactionId() {
    static int id = 1000;
    return id++;
}

// Create sample transactions for SPECIFIED users (JAN-JUL 2025)
void createSampleTransactions() {
    Transaction transactions[] = {
        // Aakarshi's transactions (January-July 2025)
        {1001, "income", 6000.0f, "Salary", "2025-01-01", "Monthly salary - Tech company", "aakarshi"},
        {1002, "expense", 1300.0f, "Rent", "2025-01-05", "Apartment rent", "aakarshi"},
        {1003, "expense", 180.0f, "Food", "2025-01-10", "Groceries", "aakarshi"},
        {1004, "expense", 120.0f, "Food", "2025-01-15", "Restaurants", "aakarshi"},
        
        {1005, "income", 6000.0f, "Salary", "2025-02-01", "Monthly salary - Tech company", "aakarshi"},
        {1006, "expense", 1300.0f, "Rent", "2025-02-05", "Apartment rent", "aakarshi"},
        {1007, "expense", 220.0f, "Food", "2025-02-12", "Groceries", "aakarshi"},
        {1008, "expense", 150.0f, "Entertainment", "2025-02-20", "Movie tickets", "aakarshi"},
        
        {1009, "income", 6000.0f, "Salary", "2025-03-01", "Monthly salary - Tech company", "aakarshi"},
        {1010, "expense", 1300.0f, "Rent", "2025-03-05", "Apartment rent", "aakarshi"},
        {1011, "expense", 250.0f, "Shopping", "2025-03-15", "New clothes", "aakarshi"},
        {1012, "expense", 100.0f, "Transport", "2025-03-22", "Fuel", "aakarshi"},
        
        {1013, "income", 6000.0f, "Salary", "2025-04-01", "Monthly salary - Tech company", "aakarshi"},
        {1014, "expense", 1300.0f, "Rent", "2025-04-05", "Apartment rent", "aakarshi"},
        {1015, "expense", 300.0f, "Food", "2025-04-10", "Groceries & dining", "aakarshi"},
        {1016, "expense", 200.0f, "Entertainment", "2025-04-18", "Concert tickets", "aakarshi"},
        
        {1017, "income", 6000.0f, "Salary", "2025-05-01", "Monthly salary - Tech company", "aakarshi"},
        {1018, "expense", 1300.0f, "Rent", "2025-05-05", "Apartment rent", "aakarshi"},
        {1019, "expense", 180.0f, "Food", "2025-05-12", "Groceries", "aakarshi"},
        {1020, "expense", 120.0f, "Transport", "2025-05-20", "Car maintenance", "aakarshi"},
        
        {1021, "income", 6000.0f, "Salary", "2025-06-01", "Monthly salary - Tech company", "aakarshi"},
        {1022, "expense", 1300.0f, "Rent", "2025-06-05", "Apartment rent", "aakarshi"},
        {1023, "expense", 400.0f, "Shopping", "2025-06-15", "Electronics", "aakarshi"},
        {1024, "expense", 150.0f, "Food", "2025-06-25", "Restaurants", "aakarshi"},
        
        {1025, "income", 6000.0f, "Salary", "2025-07-01", "Monthly salary - Tech company", "aakarshi"},
        {1026, "expense", 1300.0f, "Rent", "2025-07-05", "Apartment rent", "aakarshi"},
        {1027, "expense", 200.0f, "Food", "2025-07-10", "Groceries", "aakarshi"},
        {1028, "expense", 250.0f, "Entertainment", "2025-07-20", "Vacation", "aakarshi"},
        
        // Ruhi's transactions (January-July 2025)
        {1029, "income", 4500.0f, "Salary", "2025-01-01", "Monthly salary - Design agency", "ruhi"},
        {1030, "expense", 1100.0f, "Rent", "2025-01-05", "Studio apartment", "ruhi"},
        {1031, "expense", 120.0f, "Food", "2025-01-10", "Groceries", "ruhi"},
        {1032, "expense", 80.0f, "Supplies", "2025-01-15", "Art supplies", "ruhi"},
        
        {1033, "income", 4500.0f, "Salary", "2025-02-01", "Monthly salary - Design agency", "ruhi"},
        {1034, "expense", 1100.0f, "Rent", "2025-02-05", "Studio apartment", "ruhi"},
        {1035, "expense", 150.0f, "Food", "2025-02-12", "Groceries & dining", "ruhi"},
        {1036, "expense", 100.0f, "Shopping", "2025-02-20", "New clothes", "ruhi"},
        
        {1037, "income", 4500.0f, "Salary", "2025-03-01", "Monthly salary - Design agency", "ruhi"},
        {1038, "expense", 1100.0f, "Rent", "2025-03-05", "Studio apartment", "ruhi"},
        {1039, "expense", 200.0f, "Supplies", "2025-03-15", "Design software", "ruhi"},
        {1040, "expense", 60.0f, "Entertainment", "2025-03-22", "Movie night", "ruhi"},
        
        {1041, "income", 4500.0f, "Salary", "2025-04-01", "Monthly salary - Design agency", "ruhi"},
        {1042, "expense", 1100.0f, "Rent", "2025-04-05", "Studio apartment", "ruhi"},
        {1043, "expense", 130.0f, "Food", "2025-04-10", "Groceries", "ruhi"},
        {1044, "expense", 90.0f, "Transport", "2025-04-18", "Bus pass", "ruhi"},
        
        {1045, "income", 4500.0f, "Salary", "2025-05-01", "Monthly salary - Design agency", "ruhi"},
        {1046, "expense", 1100.0f, "Rent", "2025-05-05", "Studio apartment", "ruhi"},
        {1047, "expense", 160.0f, "Food", "2025-05-12", "Restaurants", "ruhi"},
        {1048, "expense", 120.0f, "Shopping", "2025-05-20", "Art materials", "ruhi"},
        
        {1049, "income", 4500.0f, "Salary", "2025-06-01", "Monthly salary - Design agency", "ruhi"},
        {1050, "expense", 1100.0f, "Rent", "2025-06-05", "Studio apartment", "ruhi"},
        {1051, "expense", 140.0f, "Food", "2025-06-15", "Groceries", "ruhi"},
        {1052, "expense", 180.0f, "Entertainment", "2025-06-25", "Concert", "ruhi"},
        
        {1053, "income", 4500.0f, "Salary", "2025-07-01", "Monthly salary - Design agency", "ruhi"},
        {1054, "expense", 1100.0f, "Rent", "2025-07-05", "Studio apartment", "ruhi"},
        {1055, "expense", 170.0f, "Food", "2025-07-10", "Groceries & dining", "ruhi"},
        {1056, "expense", 110.0f, "Supplies", "2025-07-20", "Design tools", "ruhi"},
        
        // Kavya's transactions (January-July 2025)
        {1057, "income", 4000.0f, "Salary", "2025-01-01", "Monthly salary - School", "kavya"},
        {1058, "expense", 900.0f, "Rent", "2025-01-05", "Shared apartment", "kavya"},
        {1059, "expense", 100.0f, "Food", "2025-01-10", "Groceries", "kavya"},
        {1060, "expense", 60.0f, "Education", "2025-01-15", "Books", "kavya"},
        
        {1061, "income", 4000.0f, "Salary", "2025-02-01", "Monthly salary - School", "kavya"},
        {1062, "expense", 900.0f, "Rent", "2025-02-05", "Shared apartment", "kavya"},
        {1063, "expense", 110.0f, "Food", "2025-02-12", "Groceries", "kavya"},
        {1064, "expense", 40.0f, "Transport", "2025-02-20", "Bus pass", "kavya"},
        
        {1065, "income", 4000.0f, "Salary", "2025-03-01", "Monthly salary - School", "kavya"},
        {1066, "expense", 900.0f, "Rent", "2025-03-05", "Shared apartment", "kavya"},
        {1067, "expense", 120.0f, "Food", "2025-03-15", "Groceries & dining", "kavya"},
        {1068, "expense", 80.0f, "Education", "2025-03-22", "Teaching materials", "kavya"},
        
        {1069, "income", 4000.0f, "Salary", "2025-04-01", "Monthly salary - School", "kavya"},
        {1070, "expense", 900.0f, "Rent", "2025-04-05", "Shared apartment", "kavya"},
        {1071, "expense", 90.0f, "Food", "2025-04-10", "Groceries", "kavya"},
        {1072, "expense", 50.0f, "Entertainment", "2025-04-18", "Books", "kavya"},
        
        {1073, "income", 4000.0f, "Salary", "2025-05-01", "Monthly salary - School", "kavya"},
        {1074, "expense", 900.0f, "Rent", "2025-05-05", "Shared apartment", "kavya"},
        {1075, "expense", 130.0f, "Food", "2025-05-12", "Restaurants", "kavya"},
        {1076, "expense", 70.0f, "Transport", "2025-05-20", "Taxi", "kavya"},
        
        {1077, "income", 4000.0f, "Salary", "2025-06-01", "Monthly salary - School", "kavya"},
        {1078, "expense", 900.0f, "Rent", "2025-06-05", "Shared apartment", "kavya"},
        {1079, "expense", 100.0f, "Food", "2025-06-15", "Groceries", "kavya"},
        {1080, "expense", 90.0f, "Education", "2025-06-25", "Online course", "kavya"},
        
        {1081, "income", 4000.0f, "Salary", "2025-07-01", "Monthly salary - School", "kavya"},
        {1082, "expense", 900.0f, "Rent", "2025-07-05", "Shared apartment", "kavya"},
        {1083, "expense", 140.0f, "Food", "2025-07-10", "Groceries & dining", "kavya"},
        {1084, "expense", 60.0f, "Entertainment", "2025-07-20", "Movie", "kavya"}
    };
    
    FILE *file = fopen("transactions.dat", "wb");
    if(file) {
        fwrite(transactions, sizeof(Transaction), 84, file); // 28 per user × 3 users
        fclose(file);
        printf("    ✅ Sample transactions created! (Jan-Jul 2025)\n");
    }
}

// Create sample budgets for SPECIFIED users (2025)
void createSampleBudgets() {
    Budget budgets[] = {
        // Aakarshi's budgets (2025)
        {"Rent", 1400.0f, "aakarshi"},
        {"Food", 400.0f, "aakarshi"},
        {"Transport", 150.0f, "aakarshi"},
        {"Entertainment", 300.0f, "aakarshi"},
        {"Shopping", 350.0f, "aakarshi"},
        
        // Ruhi's budgets (2025)
        {"Rent", 1200.0f, "ruhi"},
        {"Food", 200.0f, "ruhi"},
        {"Supplies", 200.0f, "ruhi"},
        {"Entertainment", 150.0f, "ruhi"},
        {"Shopping", 250.0f, "ruhi"},
        
        // Kavya's budgets (2025)
        {"Rent", 950.0f, "kavya"},
        {"Food", 150.0f, "kavya"},
        {"Education", 100.0f, "kavya"},
        {"Transport", 80.0f, "kavya"},
        {"Entertainment", 100.0f, "kavya"}
    };
    
    FILE *file = fopen("budgets.dat", "wb");
    if(file) {
        fwrite(budgets, sizeof(Budget), 15, file);
        fclose(file);
        printf("    ✅ Sample budgets created! (2025)\n");
    }
}
void initializeSampleData() {
    createSampleTransactions();
    createSampleBudgets();
}