#include <stdio.h>
#include "account.h"
#include "file.h"
#include "transaction.h"

int main(){
    struct Account acc[100];
    int count = 0;

    loadFromFile(acc, &count);

    int choice;

    do{
        printf("\n1.Create Account\n");
        printf("2.Deposit\n");
        printf("3.Withdraw\n");
        printf("4.View Accounts\n");
        printf("5.Delete Account\n");
        printf("6.View My Transactions\n");
        printf("7.Transfer Money\n");
        printf("8.Exit\n");

        printf("Enter Choice: ");

        if(scanf("%d",&choice) != 1){
            printf("Invalid input\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice){
            case 1:
                CreateAccount(acc,&count);
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
                if(index != -1){
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

    }while(choice != 8);

    return 0;
}