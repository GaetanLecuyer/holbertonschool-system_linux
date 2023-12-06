#include "directory_operations.h"

int main(int argc, char *argv[]) {
    int i;

    if (argc < 2) {
        listDirectory(".");
    } else {
        for (i = 1; i < argc; i++) {
            struct stat path_stat;

            if (lstat(argv[i], &path_stat) == -1) {
                fprintf(stderr, "%s: cannot access %s: %s\n", argv[0], argv[i], strerror(errno));
            } else {
                if (S_ISDIR(path_stat.st_mode)) {
                    listDirectory(argv[i]);
                } else {
                    printf("%s\n", argv[i]);
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
