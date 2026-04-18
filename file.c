#include <stdio.h>
#include "file.h"

void loadFromFile(struct Account acc[], int *count){
    FILE *fp = fopen("accounts.dat","rb");

    if(fp == NULL){
        return;
    }

    *count = fread(acc, sizeof(struct Account), 100, fp);
    printf("Loaded %d accounts\n", *count);

    fclose(fp);
}

void saveToFile(struct Account acc[], int count){
    FILE *fp = fopen("accounts.dat","wb");

    if(fp == NULL){
        printf("Error saving data!\n");
        return;
    }

    fwrite(acc, sizeof(struct Account), count, fp);

    fclose(fp);
}