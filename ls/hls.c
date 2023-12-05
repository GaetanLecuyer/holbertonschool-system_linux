#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/* Fonction de comparaison pour le tri */
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
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

    /* Open the current directory */
    dir = opendir(".");

    /* Check if opening the directory was successful */
    if (dir == NULL)
    {
        perror("Error opening directory");
        return (1);
    }

    /* Traverse the directory and store the names of each visible file/folder */
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            entries = realloc(entries, (count + 1) * sizeof(char *));
            entries[count] = strdup(entry->d_name);
            count++;
        }
    }

    /* Close the directory */
    closedir(dir);

    /* Sort the entries */
    qsort(entries, count, sizeof(char *), compare);

    /* Print the sorted entries */
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", entries[i]);
        free(entries[i]); 
    }

    /* Free the array of entries */
    free(entries);

    return (0);
}

