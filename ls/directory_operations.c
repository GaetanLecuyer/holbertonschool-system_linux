#include "directory_operations.h"
#include "entry_operations.h"

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
        fprintf(stderr, "%s: cannot open directory %s: %s\n", __FILE__, path, strerror(errno));
        return;
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

    /* Imprimer les entrées triées */
    for (i = 0; i < entries.count; i++)
    {
        printf("%s\n", entries.entries[i]);
    }

    /* Libérer la mémoire allouée pour les entrées */
    freeEntries(&entries);
}
