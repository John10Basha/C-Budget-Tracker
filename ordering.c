// ordering.c
#include <stdio.h>
#include <string.h>
#include "ordering.h"
#include "budget.h"
#include "data.h"

void sortByID(Entry entries[], int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (entries[i].ID > entries[j].ID)
            {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
}

void sortByDate(Entry entries[], int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (strcmp(entries[i].date, entries[j].date) > 0)
            {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
}

void sortByAmount(Entry entries[], int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (entries[i].amount > entries[j].amount)
            {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
}

void sortByDescription(Entry entries[], int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (strcmp(entries[i].description, entries[j].description) > 0)
            {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
}

void sortMenu()
{
    int count = 0;
    Entry *entries = readAllEntries(&count);
    if (!entries)
    {
        return;
    }

    if (count == 0)
    {
        printf("No entries found.\n");
        return;
    }

    int choice;
    printf("Sort Menu\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Amount\n");
    printf("4. Sort by Description\n");
    printf("Choice: ");
    scanf("%d", &choice);

    while (getchar() != '\n')
        ;

    switch (choice)
    {
    case 1:
        sortByID(entries, count);
        break;
    case 2:
        sortByDate(entries, count);
        break;
    case 3:
        sortByAmount(entries, count);
        break;
    case 4:
        sortByDescription(entries, count);
        break;
    default:
        printf("Invalid option.\n");
        return;
    }

    displayAllEntriesFromArray(entries, count);

    freeEntries(entries);
}
