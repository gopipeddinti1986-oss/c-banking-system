#include <stdio.h>
#include "transaction.h"
#include "file.h"
#include "account.h"

void logTransaction(int accNo, char type[], float amount){
    FILE *fp = fopen("transactions.txt", "a");

    if(fp == NULL){
        printf("Error logging transaction\n");
        return;
    }

    // 🕒 Get current time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // 🧾 Format time
    char timestamp[50];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    // 💾 Write with timestamp
    fprintf(fp, "%d %s %.2f %s\n", accNo, type, amount, timestamp);

    fclose(fp);
}

void viewTransactionsByAccount(int accNo){
    FILE *fp = fopen("transactions.txt", "r");

    if(fp == NULL){
        printf("No transaction history\n");
        return;
    }

    int fileAccNo;
    char type[20];
    float amount;
    char date[20], timeStr[20];

    printf("\n--- Transaction History ---\n");

    while(fscanf(fp, "%d %19s %f %19s %19s", 
                 &fileAccNo, type, &amount, date, timeStr) == 5){

        if(fileAccNo == accNo){
            printf("%d %s %.2f %s %s\n",
                   fileAccNo, type, amount, date, timeStr);
        }
    }

    fclose(fp);
}

void Deposit(struct Account acc[], int count){
    int index = login(acc, count);
    if(index == -1) return;

    float amount;
    printf("Enter Amount: ");
    scanf("%f", &amount);

    if(amount <= 0){
        printf("Invalid amount!\n");
        return;
    }

    acc[index].balance += amount;
    printf("Deposit successful\n");

    logTransaction(acc[index].accNo, "DEPOSIT", amount);
    saveToFile(acc, count);
}

void Withdraw(struct Account acc[], int count){
    int index = login(acc, count);
    if(index == -1) return;

    float amount;
    printf("Enter Amount: ");
    scanf("%f", &amount);

    if(amount <= 0){
        printf("Invalid amount!\n");
        return;
    }

    if(acc[index].balance < amount){
        printf("Insufficient Amount\n");
        return;
    }

    acc[index].balance -= amount;
    printf("Withdrawal successful\n");

    logTransaction(acc[index].accNo, "WITHDRAW", amount);
    saveToFile(acc, count);
}

void Transfer(struct Account acc[], int count){
    int senderIndex = login(acc, count);
    if(senderIndex == -1) return;

    int receiverAccNo;
    float amount;

    printf("Enter Receiver Account Number: ");
    scanf("%d", &receiverAccNo);

    int receiverIndex = FindAccount(acc, count, receiverAccNo);

    if(receiverIndex == -1){
        printf("Receiver account not found\n");
        return;
    }

    if(receiverIndex == senderIndex){
        printf("Cannot transfer to same account\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%f", &amount);

    if(amount <= 0){
        printf("Invalid amount\n");
        return;
    }

    if(acc[senderIndex].balance < amount){
        printf("Insufficient balance\n");
        return;
    }

    acc[senderIndex].balance -= amount;
    acc[receiverIndex].balance += amount;

    printf("Transfer successful\n");

    logTransaction(acc[senderIndex].accNo, "TRANSFER_OUT", amount);
    logTransaction(acc[receiverIndex].accNo, "TRANSFER_IN", amount);

    saveToFile(acc, count);
}