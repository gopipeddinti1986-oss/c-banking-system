#include <stdio.h>

struct Account {
    int accNo;
    char name[100];
    float balance;
    int pin;
};

void loadFromFile(struct Account acc[], int *count) {
    FILE *fp = fopen("accounts.dat", "rb");
    if (fp == NULL)
        return;

    *count = fread(acc, sizeof(struct Account), 100, fp);
    printf("Loaded %d accounts\n", *count);

    fclose(fp);
}

void saveToFile(struct Account acc[], int count) {
    FILE *fp = fopen("accounts.dat", "wb");
    if (fp == NULL) {
        printf("Error saving data!\n");
        return;
    }
    fwrite(acc, sizeof(struct Account), count, fp);
    fclose(fp);
}

void logTransaction(int accNo, char type[], float amount) {
    FILE *fp = fopen("transactions.txt", "a");
    if (fp == NULL) {
        printf("Error logging transaction\n");
        return;
    }
    fprintf(fp, "%d %s %.2f\n", accNo, type, amount);
    fclose(fp);
}

void viewTransactionsByAccount(int accNo) {
    FILE *fp = fopen("transactions.txt", "r");
    if (fp == NULL) {
        printf("No transaction history\n");
        return;
    }

    int fileAccNo;
    char type[20];
    float amount;

    printf("\n--- Transaction History ---\n");

    while (fscanf(fp, "%d %19s %f", &fileAccNo, type, &amount) == 3) {
        if (fileAccNo == accNo) {
            printf("%d %s %.2f\n", fileAccNo, type, amount);
        }
    }
    fclose(fp);
}

int FindAccount(struct Account acc[], int count, int accNo) {
    for (int i = 0; i < count; i++) {
        if (acc[i].accNo == accNo)
            return i;
    }
    return -1;
}

int login(struct Account acc[], int count) {
    int accNo, pin;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    int index = FindAccount(acc, count, accNo);
    if (index == -1) {
        printf("Account not found\n");
        return -1;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (acc[index].pin != pin) {
        printf("Incorrect PIN\n");
        return -1;
    }

    return index;
}

void CreateAccount(struct Account acc[], int *count) {
    if (*count >= 100) {
        printf("Account limit reached!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc[*count].accNo);

    if (FindAccount(acc, *count, acc[*count].accNo) != -1) {
        printf("Account already exists\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", acc[*count].name);

    printf("Set 4-digit PIN: ");
    scanf("%d", &acc[*count].pin);

    if (acc[*count].pin < 1000 || acc[*count].pin > 9999) {
        printf("Invalid PIN\n");
        return;
    }

    printf("Enter initial balance: ");
    scanf("%f", &acc[*count].balance);

    (*count)++;
    saveToFile(acc, *count);
}

void Deposit(struct Account acc[], int count) {
    int index = login(acc, count);
    if (index == -1)
        return;

    float amount;
    printf("Enter Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    acc[index].balance += amount;
    printf("Deposit successful\n");

    logTransaction(acc[index].accNo, "DEPOSIT", amount);
    saveToFile(acc, count);
}

void Withdraw(struct Account acc[], int count) {
    int index = login(acc, count);
    if (index == -1)
        return;

    float amount;
    printf("Enter Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (acc[index].balance < amount) {
        printf("Insufficient Amount\n");
        return;
    }

    acc[index].balance -= amount;
    printf("Withdrawal successful\n");

    logTransaction(acc[index].accNo, "WITHDRAW", amount);
    saveToFile(acc, count);
}

void Transfer(struct Account acc[], int count) {
    int senderIndex = login(acc, count);
    if (senderIndex == -1)
        return;

    int receiverAccNo;
    float amount;

    printf("Enter Receiver Account Number: ");
    scanf("%d", &receiverAccNo);

    int receiverIndex = FindAccount(acc, count, receiverAccNo);

    if (receiverIndex == -1) {
        printf("Receiver account not found\n");
        return;
    }

    if (receiverIndex == senderIndex) {
        printf("Cannot transfer to same account\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount\n");
        return;
    }

    if (acc[senderIndex].balance < amount) {
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

void DeleteAccount(struct Account acc[], int *count) {
    if (*count == 0) {
        printf("No accounts available\n");
        return;
    }

    int index = login(acc, *count);
    if (index == -1)
        return;

    logTransaction(acc[index].accNo, "DELETE", acc[index].balance);

    for (int i = index; i < *count - 1; i++) {
        acc[i] = acc[i + 1];
    }

    (*count)--;

    saveToFile(acc, *count);

    printf("Account deleted successfully\n");
}

void DisplayAccounts(struct Account acc[], int count) {
    if (count == 0) {
        printf("No accounts available\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nAccount Number: %d\n", acc[i].accNo);
        printf("Name: %s\n", acc[i].name);
        printf("Balance: %.2f\n", acc[i].balance);
    }
}

int main() {
    struct Account acc[100];
    int count = 0;

    loadFromFile(acc, &count);

    int choice;

    do {
        printf("\n1.Create Account\n");
        printf("2.Deposit\n");
        printf("3.Withdraw\n");
        printf("4.View Accounts\n");
        printf("5.Delete Account\n");
        printf("6.View My Transactions\n");
        printf("7.Transfer Money\n");
        printf("8.Exit\n");

        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                CreateAccount(acc, &count);
                break;
            case 2:
                Deposit(acc, count);
                break;
            case 3:
                Withdraw(acc, count);
                break;
            case 4:
                DisplayAccounts(acc, count);
                break;
            case 5:
                DeleteAccount(acc, &count);
                break;
            case 6: {
                int index = login(acc, count);
                if (index != -1) {
                    viewTransactionsByAccount(acc[index].accNo);
                }
                break;
            }
            case 7:
                Transfer(acc, count);
                break;
            case 8:
                break;
            default:
                printf("Invalid Choice\n");
        }

    } while (choice != 8);

    return 0;
}
