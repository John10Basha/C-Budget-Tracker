// budget.c
#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "data.h"
#include <time.h>

void displayAllEntries()
{
    int count = 0;
    Entry *entries = readAllEntries(&count);
    if (!entries)
    {
        return;
    }
    displayAllEntriesFromArray(entries, count);
    freeEntries(entries);
}

void displayAllEntriesFromArray(Entry entries[], int count)
{
    printf("Finances Summary\n");
    printf("=================\n");
    printf("ID      Date         Type        Category      Description        Amount\n");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-8d%-13s%-12s%-14s%-19s$%.2lf\n",
               entries[i].ID, entries[i].date, entries[i].type,
               entries[i].category, entries[i].description, entries[i].amount);
    }

    if (count == 0)
        printf("No entries were read from the file.\n");
}

void displayExpenseDistribution()
{
    int count = 0;
    Entry *entries = readAllEntries(&count);
    if (!entries)
    {
        return;
    }

    double income = 0, expenses = 0, needs = 0, wants = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(entries[i].type, "income") == 0)
            income += entries[i].amount;
        else if (strcmp(entries[i].type, "expense") == 0)
        {
            expenses += entries[i].amount;
            if (strcmp(entries[i].category, "Needs") == 0)
                needs += entries[i].amount;
            else if (strcmp(entries[i].category, "Wants") == 0)
                wants += entries[i].amount;
        }
    }

    printf("\nExpense Distribution Summary\n");
    printf("============================\n");
    printf("Total Income: $%.2f\n", income);
    printf("Total Expenses: $%.2f\n", expenses);
    printf("Needs: $%.2f (%.2f%% of expenses, %.2f%% of income)\n",
           needs,
           expenses > 0 ? (needs / expenses) * 100 : 0,
           income > 0 ? (needs / income) * 100 : 0);
    printf("Wants: $%.2f (%.2f%% of expenses, %.2f%% of income)\n",
           wants,
           expenses > 0 ? (wants / expenses) * 100 : 0,
           income > 0 ? (wants / income) * 100 : 0);
    printf("Net Balance: $%.2f\n", income - expenses);

    freeEntries(entries);
}

void addEntry()
{
    int count = 0;
    Entry *entries = readAllEntries(&count);
    if (!entries)
    {
        return;
    }

    int newID = 1;
    for (int i = 0; i < count; i++)
    {
        if (entries[i].ID >= newID)
            newID = entries[i].ID + 1;
    }

    Entry newEntry;
    newEntry.ID = newID;

    char use_today;
    printf("Use today's date? (y/n): ");
    scanf(" %c", &use_today);
    getchar();

    if (use_today == 'y' || use_today == 'Y')
    {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        strftime(newEntry.date, sizeof(newEntry.date), "%Y-%m-%d", tm_info);
    }
    else
    {
        printf("Enter date (YYYY-MM-DD): ");
        fgets(newEntry.date, sizeof(newEntry.date), stdin);
        newEntry.date[strcspn(newEntry.date, "\n")] = 0;
    }

    printf("Type (income/expense): ");
    fgets(newEntry.type, sizeof(newEntry.type), stdin);
    newEntry.type[strcspn(newEntry.type, "\n")] = 0;

    printf("Category: ");
    fgets(newEntry.category, sizeof(newEntry.category), stdin);
    newEntry.category[strcspn(newEntry.category, "\n")] = 0;

    printf("Description: ");
    fgets(newEntry.description, sizeof(newEntry.description), stdin);
    newEntry.description[strcspn(newEntry.description, "\n")] = 0;

    printf("Amount: $");
    scanf("%lf", &newEntry.amount);
    getchar();

    if (newEntry.amount < 0)
    {
        printf("Error: Amount cannot be negative.\n");
        return;
    }

    FILE *fp = fopen("finances.txt", "a");
    if (fp == NULL)
    {
        perror("Error opening file to write new entry");
        return;
    }

    fprintf(fp, "\n%d|%s|%s|%s|%s|%.2f",
            newEntry.ID,
            newEntry.date,
            newEntry.type,
            newEntry.category,
            newEntry.description,
            newEntry.amount);

    fclose(fp);

    printf("Entry added successfully with ID: %d\n", newEntry.ID);

    freeEntries(entries);
}

void modifyEntry()
{
    int count = 0;
    Entry *entries = readAllEntries(&count);
    if (!entries)
    {
        return;
    }

    if (count == 0)
    {
        printf("No entries available to modify.\n");
        return;
    }

    // Display all entries with ID
    displayAllEntriesFromArray(entries, count);

    int targetID, choice;
    printf("\nEnter ID of entry to modify: ");
    scanf("%d", &targetID);
    getchar();

    // Find the entry
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (entries[i].ID == targetID)
        {
            found = 1;

            printf("\nCurrent Details:\n");
            printf("ID: %d\n", entries[i].ID);
            printf("Date: %s\n", entries[i].date);
            printf("Type: %s\n", entries[i].type);
            printf("Category: %s\n", entries[i].category);
            printf("Description: %s\n", entries[i].description);
            printf("Amount: $%.2f\n", entries[i].amount);

            printf("\nWhat would you like to modify?\n");
            printf("1. Date\n");
            printf("2. Amount\n");
            printf("Choice: ");
            scanf("%d", &choice);
            getchar();

            if (choice == 1)
            {
                printf("Enter new date (YYYY-MM-DD): ");
                fgets(entries[i].date, sizeof(entries[i].date), stdin);
                entries[i].date[strcspn(entries[i].date, "\n")] = 0;
            }
            else if (choice == 2)
            {
                double newAmount;
                printf("Enter new amount: $");
                scanf("%lf", &newAmount);
                getchar();

                if (newAmount < 0)
                {
                    printf("Error: Amount cannot be negative.\n");
                    return;
                }

                entries[i].amount = newAmount;
            }
            else
            {
                printf("Invalid choice.\n");
                return;
            }

            break;
        }
    }

    if (!found)
    {
        printf("Entry with ID %d not found.\n", targetID);
        return;
    }

    FILE *fp = fopen("finances.txt", "w");
    if (fp == NULL)
    {
        perror("Error opening file to overwrite");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d|%s|%s|%s|%s|%.2f\n",
                entries[i].ID,
                entries[i].date,
                entries[i].type,
                entries[i].category,
                entries[i].description,
                entries[i].amount);
    }

    fclose(fp);

    printf("Entry updated successfully.\n");

    freeEntries(entries);
}

void filterByMonth()
{
    int year, month;
    printf("Enter year (YYYY): ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    getchar();

    char prefix[8];
    snprintf(prefix, sizeof(prefix), "%04d-%02d", year, month);

    int count = 0;
    Entry *entries = readAllEntries(&count);
    if (!entries)
    {
        return;
    }

    printf("\nEntries for %s:\n", prefix);
    printf("ID      Date         Type        Category      Description        Amount\n");
    printf("----------------------------------------------------------------------------\n");

    int matches = 0;
    for (int i = 0; i < count; i++)
    {
        if (strncmp(entries[i].date, prefix, 7) == 0)
        {
            printf("%-8d%-13s%-12s%-14s%-19s$%.2lf\n",
                   entries[i].ID,
                   entries[i].date,
                   entries[i].type,
                   entries[i].category,
                   entries[i].description,
                   entries[i].amount);
            matches++;
        }
    }

    if (matches == 0)
    {
        printf("No entries found for %s.\n", prefix);
    }

    freeEntries(entries);
}
