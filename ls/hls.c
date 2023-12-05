#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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
    int i = 0;

    if (list->count == list->capacity)
    {
        /* Si la capacité est atteinte, doubler la taille du tableau */
        list->capacity *= 2;
        list->entries = (char **)realloc(list->entries, list->capacity * sizeof(char *));
    }

    /* Allouer de la mémoire pour le nouveau nom */
    list->entries[list->count] = (char *)malloc(256);
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
    int x = 0, y = 0;
    int z = 0;

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
            char temp[256];
            while (entries.entries[j][x] != '\0' && entries.entries[j + 1][y] != '\0')
            {
                if (entries.entries[j][x] < entries.entries[j + 1][y])
                {
                    temp[x + y] = entries.entries[j][x];
                    x++;
                }
                else
                {
                    temp[x + y] = entries.entries[j + 1][y];
                    y++;
                }
            }

            while (entries.entries[j][x] != '\0')
            {
                temp[x + y] = entries.entries[j][x];
                x++;
            }

            while (entries.entries[j + 1][y] != '\0')
            {
                temp[x + y] = entries.entries[j + 1][y];
                y++;
            }

            temp[x + y] = '\0';

            while (temp[z] != '\0')
            {
                entries.entries[j][z] = temp[z];
                z++;
            }
            entries.entries[j][z] = '\0';
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
