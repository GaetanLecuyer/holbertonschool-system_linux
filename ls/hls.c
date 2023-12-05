#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define INITIAL_CAPACITY 10

/* Structure pour stocker les entrées */
typedef struct
{
    char **entries;
    int count;
    int capacity;
} EntryList;

/* Initialiser la liste d'entrées */
void initializeList(EntryList *list)
{
    list->entries = (char **)malloc(INITIAL_CAPACITY * sizeof(char *));
    list->count = 0;
    list->capacity = INITIAL_CAPACITY;
}

/* Ajouter une entrée à la liste */
void addEntry(EntryList *list, const char *name)
{
    if (list->count == list->capacity)
    {
        /* Si la capacité est atteinte, doubler la taille du tableau */
        list->capacity *= 2;
        list->entries = (char **)realloc(list->entries, list->capacity * sizeof(char *));
    }

    /* Allouer de la mémoire pour le nouveau nom */
    list->entries[list->count] = (char *)malloc(strlen(name) + 1);
    strcpy(list->entries[list->count], name);
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
    free(list->entries);
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    DIR *dir;
    struct dirent *entry;
    EntryList entries;
    int i, j;

    /* Initialiser la liste d'entrées */
    initializeList(&entries);

    /* Open the current directory */
    dir = opendir(".");

    /* Check if opening the directory was successful */
    if (dir == NULL)
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    /* Traverse the directory and store the names of each visible file/folder */
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            addEntry(&entries, entry->d_name);
        }
    }

    /* Close the directory */
    closedir(dir);

    /* Bubble Sort the entries (simple sorting algorithm) */
    for (i = 0; i < entries.count - 1; i++)
    {
        for (j = 0; j < entries.count - i - 1; j++)
        {
            if (strcmp(entries.entries[j], entries.entries[j + 1]) > 0)
            {
                char *temp = entries.entries[j];
                entries.entries[j] = entries.entries[j + 1];
                entries.entries[j + 1] = temp;
            }
        }
    }

    /* Print the sorted entries */
    for (i = 0; i < entries.count; i++)
    {
        printf("%s\n", entries.entries[i]);
    }

    /* Free the array of entries */
    freeEntries(&entries);

    return EXIT_SUCCESS;
}
