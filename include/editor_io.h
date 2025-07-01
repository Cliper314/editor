#ifndef EDITOR_IO_H
#define EDITOR_IO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define INIT_CAPACITY 10

typedef struct {
    char *content;
    int count;
    int lenth;
    int capacity;
} row;

void add_row(row *rows, int *num_rows, const char *content_in);
void initialize_row(row *r);

#endif