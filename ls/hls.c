#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

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
int compareEntries(const char *a, const char *b);

/* Initialiser la liste d'entrées */
void initializeList(EntryList *list);

/* Ajouter une entrée à la liste */
void addEntry(EntryList *list, const char *name);

/* Libérer la mémoire allouée pour les entrées */
void freeEntries(EntryList *list);

/* Trier les entrées par tri à bulles sans utiliser strcmp */
void bubbleSort(EntryList *list);

/* Fonction pour comparer deux chaînes sans utiliser strcmp */
int compareEntries(const char *a, const char *b);

/* Fonction pour afficher le contenu d'un répertoire */
void listDirectory(const char *path);

int main(int argc, char *argv[]);

/* Fonction pour comparer deux chaînes sans utiliser strcmp */
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

/* Fonction pour afficher le contenu d'un répertoire */
void listDirectory(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    EntryList entries;
    int i;

    /* Initialiser la liste d'entrées */
    initializeList(&entries);

    /* Ouvrir le répertoire spécifié */
    dir = opendir(path);

    /* Vérifier si l'ouverture du répertoire a réussi */
    if (dir == NULL)
    {
        fprintf(stderr, "%s: ", argv[0]);
        perror("cannot open directory");
        exit(EXIT_FAILURE);
    }

    /* Parcourir le répertoire et stocker les noms de chaque fichier/dossier visible */
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            addEntry(&entries, entry->d_name);
        }
    }

    /* Fermer le répertoire */
    closedir(dir);

    /* Trier les entrées par tri à bulles */
    bubbleSort(&entries);

    /* Afficher les entrées triées */
    printf("%s:\n", path);
    for (i = 0; i < entries.count; i++)
    {
        printf("%s\n", entries.entries[i]);
    }

    /* Libérer la mémoire allouée pour les entrées */
    freeEntries(&entries);
}

int main(int argc, char *argv[])
{
    int i;

    /* Si aucun argument n'est fourni, lister le répertoire actuel */
    if (argc == 1)
    {
        listDirectory(".");
    }
    else
    {
        /* Pour chaque argument, lister le répertoire spécifié */
        for (i = 1; i < argc; i++)
        {
            listDirectory(argv[i]);
            if (i < argc - 1)
                printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
