#ifndef DIRECTORY_OPERATIONS_H
#define DIRECTORY_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include "entry_operations.h"

#define INITIAL_CAPACITY 10
#define MAX_NAME_LENGTH 256

void listDirectory(const char *path);

#endif