#include <stdio.h>
#include "account.h"
#include "file.h"
#include "transaction.h"

int FindAccount(struct Account acc[], int count, int accNo){
    for(int i = 0; i < count; i++){
        if(acc[i].accNo == accNo){
            return i;
        }
    }
    return -1;
}

int login(struct Account acc[], int count){
    int accNo, pin;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = FindAccount(acc, count, accNo);
    if(index == -1){
        printf("Account not found\n");
        return -1;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if(acc[index].pin != pin){
        printf("Incorrect PIN\n");
        return -1;
    }

    return index;
}

void CreateAccount(struct Account acc[], int *count){
    if(*count >= 100){
        printf("Account limit reached\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d",&acc[*count].accNo);

    if(FindAccount(acc, *count, acc[*count].accNo) != -1){
        printf("Account already exists\n");
        return;
    }
    printf("Enter Name: ");
    scanf(" %[^\n]",acc[*count].name);

    printf("Set 4-digit PIN: ");
    scanf("%d",&acc[*count].pin);

    printf("Enter initial balance: ");
    scanf("%f",&acc[*count].balance);
    if(acc[*count].balance < 0){
        printf("Invalid balance\n");
        return;
    }

    (*count)++;

    saveToFile(acc, *count);
}

void DeleteAccount(struct Account acc[], int *count){
    if(*count == 0){
        printf("No accounts available\n");
        return;
    }

    int index = login(acc, *count);
    if(index == -1) return;

    logTransaction(acc[index].accNo, "DELETE", acc[index].balance);

    for(int i = index; i < *count - 1; i++){
        acc[i] = acc[i+1];
    }

    (*count)--;

    saveToFile(acc, *count);

    printf("Account deleted successfully\n");
}

void DisplayAccounts(struct Account acc[], int count){
    if(count == 0){
        printf("No accounts available\n");
        return;
    }

    for(int i = 0; i < count; i++){
        printf("\nAccount Number: %d\n", acc[i].accNo);
        printf("Name: %s\n", acc[i].name);
        printf("Balance: %.2f\n", acc[i].balance);
    }
}