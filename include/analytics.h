#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "auth.h"

void showSpendingByCategory(const char *username);
void generateMonthlyReport(const char *username);
void displaySpendingChart(const char *username);

#endif