// entry_operations.h
#ifndef ENTRY_OPERATIONS_H
#define ENTRY_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 10
#define MAX_NAME_LENGTH 256

typedef struct {
    char *entries[INITIAL_CAPACITY];
    int count;
    int capacity;
} EntryList;

void initializeList(EntryList *list);
void addEntry(EntryList *list, const char *name);
void freeEntries(EntryList *list);
void bubbleSort(EntryList *list);
int compareEntries(const char *a, const char *b);

#endif // ENTRY_OPERATIONS_H
