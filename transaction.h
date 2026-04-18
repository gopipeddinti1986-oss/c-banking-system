#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "account.h"
#include <time.h>

void Deposit(struct Account acc[], int count);
void Withdraw(struct Account acc[], int count);
void Transfer(struct Account acc[], int count);
void logTransaction(int accNo, char type[], float amount);
void viewTransactionsByAccount(int accNo);

#endif