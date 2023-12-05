#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/* Fonction pour ajouter une entrée à la liste */
void addEntry(char ***entries, int *count, const char *name)
{
    (*entries) = realloc((*entries), ((*count) + 1) * sizeof(char *));
    (*entries)[(*count)] = strdup(name);
    (*count)++;
}

/* Fonction pour libérer la mémoire allouée pour les entrées */
void freeEntries(char ***entries, int count)
{
    for (int i = 0; i < count; i++)
    {
        free((*entries)[i]);
    }
    free(*entries);
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
    char **entries = NULL;
    int count = 0;
    int i, j;

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
        if (entry->d_name[0] != '.') // Ignore hidden files and directories
        {
            addEntry(&entries, &count, entry->d_name);
        }
    }

    /* Close the directory */
    closedir(dir);

    /* Bubble Sort the entries (simple sorting algorithm) */
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (strcmp(entries[j], entries[j + 1]) > 0)
            {
                char *temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }

    /* Print the sorted entries */
    for (i = 0; i < count; i++)
    {
        printf("%s\n", entries[i]);
    }

    /* Free the array of entries */
    freeEntries(&entries, count);

    return (EXIT_SUCCESS);
}
