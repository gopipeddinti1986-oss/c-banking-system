#ifndef FILE_H
#define FILE_H

#include "account.h"

void loadFromFile(struct Account acc[], int *count);
void saveToFile(struct Account acc[], int count);

#endif