#include "entry_operations.h"

void initializeList(EntryList *list) {
    list->count = 0;
    list->capacity = INITIAL_CAPACITY;
}

void addEntry(EntryList *list, const char *name)
{
    int i = 0;

    if (list->count == list->capacity)
    {
        fprintf(stderr, "Error: Maximum capacity reached\n");
        exit(EXIT_FAILURE);
    }

    /* Allouer de la mémoire pour le nouveau nom */
    list->entries[list->count] = (char *)malloc(MAX_NAME_LENGTH);
    while (name[i] != '\0')
    {
        list->entries[list->count][i] = name[i];
        i++;
    }
    list->entries[list->count][i] = '\0';

    list->count++;
}

/* Libérer la mémoire allouée pour les entrées */
void freeEntries(EntryList *list)
{
    int i;

    for (i = 0; i < list->count; i++)
    {
        free(list->entries[i]);
    }
}

/* Trier les entrées par tri à bulles sans utiliser strcmp */
void bubbleSort(EntryList *list)
{
    int i, j;
    char *temp;

    for (i = 0; i < list->count - 1; i++)
    {
        for (j = 0; j < list->count - i - 1; j++)
        {
            if (compareEntries(list->entries[j], list->entries[j + 1]) > 0)
            {
                temp = list->entries[j];
                list->entries[j] = list->entries[j + 1];
                list->entries[j + 1] = temp;
            }
        }
    }
}

int compareEntries(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        char charA = (*a >= 'A' && *a <= 'Z') ? (*a + 32) : *a;
        char charB = (*b >= 'A' && *b <= 'Z') ? (*b + 32) : *b;

        if (charA < charB)
            return -1;
        else if (charA > charB)
            return 1;

        a++;
        b++;
    }

    if (*a == '\0' && *b != '\0')
        return -1;
    else if (*a != '\0' && *b == '\0')
        return 1;

    return 0;
}
