// ordering.h
#ifndef ORDERING_H
#define ORDERING_H

#include "data.h"

void sortMenu();
void sortByID(Entry entries[], int count);
void sortByDate(Entry entries[], int count);
void sortByAmount(Entry entries[], int count);
void sortByDescription(Entry entries[], int count);

#endif
