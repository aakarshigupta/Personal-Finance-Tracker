#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/auth.h"

void clearScreen() {
    system("clear");
}

void printHeader(const char* title) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║%*s%*s║\n", (int)(30 + strlen(title)/2), title, (int)(30 - strlen(title)/2), "");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

void displayWelcomeScreen() {
    clearScreen();
    printf("\n\n");
    printf("    ███████╗██╗███╗   ██╗ █████╗ ███╗   ██╗ ██████╗ ███████╗\n");
    printf("    ██╔════╝██║████╗  ██║██╔══██╗████╗  ██║██╔════╝ ██╔════╝\n");
    printf("    █████╗  ██║██╔██╗ ██║███████║██╔██╗ ██║██║      █████╗  \n");
    printf("    ██╔══╝  ██║██║╚██╗██║██╔══██║██║╚██╗██║██║      ██╔══╝  \n");
    printf("    ██║     ██║██║ ╚████║██║  ██║██║ ╚████║╚██████╔╝███████╗\n");
    printf("    ╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝\n");
    printf("\n");
    printf("                💰 SMART PERSONAL FINANCE TRACKER 💰\n");
    printf("             ==========================================\n\n");
}

// Create pre-loaded users with SPECIFIED passwords
void createSampleUsers() {
    User users[3] = {
        {"aakarshi", "pyaraghar25"},
        {"ruhi", "ruhi1"}, 
        {"kavya", "kavya1"}
    };
    
    FILE *file = fopen(USERS_FILE, "wb");
    if(file) {
        fwrite(users, sizeof(User), 3, file);
        fclose(file);
        printf("    ✅ Pre-loaded users created successfully!\n");
    } else {
        printf("    ❌ ERROR: Could not create users file!\n");
    }
}

// Display user selection screen
void displayUserSelection() {
    printHeader("👥 SELECT USER");
    printf("    Choose a user to login:\n\n");
    printf("    1. 👩‍💼 Aakarshi (Software Engineer)\n");
    printf("        💼 Income: $6,000 | 🏠 Rent: $1,300 | 🍔 Food: $350\n");
    printf("        🔑 Password: pyaraghar25\n\n");
    
    printf("    2. 👩‍🎨 Ruhi (Graphic Designer)\n");
    printf("        💼 Income: $4,500 | 🏠 Rent: $1,100 | 🎨 Supplies: $200\n");
    printf("        🔑 Password: ruhi1\n\n");
    
    printf("    3. 👩‍🏫 Kavya (Teacher)\n");
    printf("        💼 Income: $4,000 | 🏠 Rent: $900 | 📚 Education: $150\n");
    printf("        🔑 Password: kavya1\n\n");
    
    printf("    Choose an option (1-3): ");
}

// User selection function
void selectUser(char *currentUser) {
    int choice;
    displayUserSelection();
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            strcpy(currentUser, "aakarshi");
            printf("\n    ✅ Welcome back, Aakarshi! 👩‍💼\n");
            break;
        case 2:
            strcpy(currentUser, "ruhi");
            printf("\n    ✅ Welcome back, Ruhi! 👩‍🎨\n");
            break;
        case 3:
            strcpy(currentUser, "kavya");
            printf("\n    ✅ Welcome back, Kavya! 👩‍🏫\n");
            break;
        default:
            printf("\n    ❌ Invalid selection!\n");
            return;
    }
    printf("    Press Enter to continue...");
    getchar(); getchar();
}

void displayLoginScreen() {
    printHeader("🔐 LOGIN");
    printf("    Please enter your credentials:\n\n");
}

void displayRegisterScreen() {
    printHeader("📝 REGISTER");
    printf("    Create your account:\n\n");
}

int userExists(const char *username) {
    FILE *file = fopen(USERS_FILE, "rb");
    User user;
    
    if(file) {
        while(fread(&user, sizeof(User), 1, file)) {
            if(strcmp(user.username, username) == 0) {
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    }
    return 0;
}

int registerUser() {
    User newUser;
    
    displayRegisterScreen();
    
    printf("    👤 Username: ");
    scanf("%s", newUser.username);
    
    if(userExists(newUser.username)) {
        printf("\n    ❌ Username already exists! Please choose another.\n");
        printf("    Press Enter to continue...");
        getchar(); getchar();
        return 0;
    }
    
    printf("    🔑 Password: ");
    scanf("%s", newUser.password);
    
    FILE *file = fopen(USERS_FILE, "ab");
    if(file) {
        fwrite(&newUser, sizeof(User), 1, file);
        fclose(file);
        printf("\n    ✅ Registration successful! You can now login.\n");
        printf("    Press Enter to continue...");
        getchar(); getchar();
        return 1;
    }
    return 0;
}

int loginUser(char *currentUser) {
    User user, inputUser;
    
    displayLoginScreen();
    
    printf("    👤 Username: ");
    scanf("%s", inputUser.username);
    printf("    🔑 Password: ");
    scanf("%s", inputUser.password);
    
    // HARDCODED USER CHECK (Primary method)
    if(strcmp(inputUser.username, "aakarshi") == 0 && strcmp(inputUser.password, "pyaraghar25") == 0) {
        strcpy(currentUser, "aakarshi");
        printf("\n    ✅ Login successful! Welcome back, Aakarshi! 👩‍💼\n");
        printf("    Press Enter to continue...");
        getchar(); getchar();
        return 1;
    }
    if(strcmp(inputUser.username, "ruhi") == 0 && strcmp(inputUser.password, "ruhi1") == 0) {
        strcpy(currentUser, "ruhi");
        printf("\n    ✅ Login successful! Welcome back, Ruhi! 👩‍🎨\n");
        printf("    Press Enter to continue...");
        getchar(); getchar();
        return 1;
    }
    if(strcmp(inputUser.username, "kavya") == 0 && strcmp(inputUser.password, "kavya1") == 0) {
        strcpy(currentUser, "kavya");
        printf("\n    ✅ Login successful! Welcome back, Kavya! 👩‍🏫\n");
        printf("    Press Enter to continue...");
        getchar(); getchar();
        return 1;
    }
    
    printf("\n    ❌ Invalid username or password! Please try again.\n");
    printf("    Press Enter to continue...");
    getchar(); getchar();
    return 0;
}