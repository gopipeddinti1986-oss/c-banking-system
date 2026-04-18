#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Account {
    int accNo;
    char name[100];
    float balance;
    int pin;
};

int FindAccount(struct Account acc[], int count, int accNo);
void CreateAccount(struct Account acc[], int *count);
void DeleteAccount(struct Account acc[], int *count);
int login(struct Account acc[], int count);
void DisplayAccounts(struct Account acc[], int count);

#endif