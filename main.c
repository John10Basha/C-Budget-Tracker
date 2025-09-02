// main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data.h"
#include "budget.h"
#include "ordering.h"

int main()
{

    int choice;
    bool keep_running_code = true;

    while (keep_running_code)
    {
        system("clear");

        printf("Budget Tracking System\n");
        printf("========================\n");
        printf("1. Display all entries\n");
        printf("2. Expense Distribution\n");
        printf("3. Sort Entries\n");
        printf("4. Add Income/Expense Entry\n");
        printf("5. Modify Entry\n");
        printf("6. Filter by Month\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            // printf("we are in 1\n\n");
            displayAllEntries();
            break;
        case 2:
            // printf("we are in 2\n\n");
            displayExpenseDistribution();
            break;
        case 3:
            // printf("we are in 3\n\n");
            sortMenu();
            break;
        case 4:
            // printf("we are in 4\n\n");
            addEntry();
            break;
        case 5:
            // printf("we are in 5\n\n");
            modifyEntry();
            break;
        case 6:
            // printf("we are in 6\n\n");
            filterByMonth();
            break;
        case 7:
            printf("Goodbye and thanks for using our budget tracker app\n\n");
            keep_running_code = false;
            break;
        default:
            printf("you need to pick a number please\n");
            break;
        }

        if (keep_running_code)
        {
            printf("Press Enter to continue...");
            getchar();
        }
    }

    return 0;
}