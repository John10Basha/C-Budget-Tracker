#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

Entry *readAllEntries(int *count)
{
    FILE *fp = fopen("finances.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        *count = 0;
        return NULL;
    }

    int capacity = INITIAL_CAPACITY;
    Entry *entries = malloc(capacity * sizeof(Entry));
    if (!entries)
    {
        perror("Memory allocation failed");
        fclose(fp);
        *count = 0;
        return NULL;
    }

    *count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp))
    {
        if (*count >= capacity)
        {
            capacity *= 2;
            Entry *temp = realloc(entries, capacity * sizeof(Entry));
            if (!temp)
            {
                perror("Memory reallocation failed");
                free(entries);
                fclose(fp);
                *count = 0;
                return NULL;
            }
            entries = temp;
        }

        int parsed = sscanf(line, "%d|%10s|%19[^|]|%19[^|]|%99[^|]|%lf",
                            &entries[*count].ID,
                            entries[*count].date,
                            entries[*count].type,
                            entries[*count].category,
                            entries[*count].description,
                            &entries[*count].amount);

        if (parsed == 6)
            (*count)++;
        else
            fprintf(stderr, "Warning: Skipped malformed line: %s", line);
    }

    fclose(fp);
    return entries;
}

void freeEntries(Entry *entries)
{
    free(entries);
}
