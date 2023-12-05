#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define INITIAL_CAPACITY 10
#define MAX_NAME_LENGTH 256

/* Structure pour stocker les entrées */
typedef struct
{
    char *entries[INITIAL_CAPACITY];
    int count;
    int capacity;
} EntryList;

/* Fonction pour comparer deux chaînes sans utiliser strcmp */
int compareStrings(const char *a, const char *b);

/* Initialiser la liste d'entrées */
void initializeList(EntryList *list)
{
    list->count = 0;
    list->capacity = INITIAL_CAPACITY;
}

/* Ajouter une entrée à la liste */
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

/* Trier les entrées par tri par insertion sans utiliser strcmp */
void insertionSort(EntryList *list)
{
    int i, j;
    char *key;

    for (i = 1; i < list->count; i++)
    {
        key = list->entries[i];
        j = i - 1;

        while (j >= 0 && compareStrings(list->entries[j], key) > 0)
        {
            list->entries[j + 1] = list->entries[j];
            j = j - 1;
        }

        list->entries[j + 1] = key;
    }
}

/* Fonction pour comparer deux chaînes sans utiliser strcmp */
int compareStrings(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0' && *a == *b)
    {
        a++;
        b++;
    }

    return (*a > *b) - (*a < *b);
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
    int i;

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

    /* Trier les entrées par tri par insertion */
    insertionSort(&entries);

    /* Imprimer les entrées triées */
    for (i = 0; i < entries.count; i++)
    {
        printf("%s\n", entries.entries[i]);
    }

    /* Libérer la mémoire allouée pour les entrées */
    freeEntries(&entries);

    return EXIT_SUCCESS;
}
