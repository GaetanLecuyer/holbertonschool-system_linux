#include <stdio.h>
#include <dirent.h>
#include <string.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    DIR *dir;
    struct dirent *entry;

    /* Open the current directory */
    dir = opendir(".");

    /* Check if opening the directory was successful */
    if (dir == NULL)
    {
        perror("Error opening directory");
        return (1);
    }

    /* Traverse the directory and print the name of each visible file/folder */
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            printf("%s\n", entry->d_name);
        }
    }

    /* Close the directory */
    closedir(dir);

    return (0);
}

