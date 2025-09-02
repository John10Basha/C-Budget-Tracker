// data.h
#ifndef DATA_H
#define DATA_H

#define INITIAL_CAPACITY 10

typedef struct
{
    int ID;
    char date[100];
    char type[100];
    char category[100];
    char description[100];
    double amount;
} Entry;

Entry *readAllEntries(int *count);
void freeEntries(Entry *entries);

#endif