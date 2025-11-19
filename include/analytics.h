#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "auth.h"


void showSpendingByCategory(const char *username);
void generateMonthlyReportOld(const char *username);
void displaySpendingChart(const char *username);

void viewMonthlyTransactions(const char *username, const char *month);
void showMonthlyAnalytics(const char *username, const char *month);
void generateMonthlyReport(const char *username, const char *month);
void checkBudgetStatus(const char *username, const char *month);

void debugCheckTransactions(const char *username);

#endif