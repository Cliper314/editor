#include "editor_io.h"


void add_row(row *rows, int *num_rows, const char *content_in) {
    if (*num_rows >= rows->capacity) {
        rows->capacity *= 2; // 扩展容量
        rows = realloc(rows, rows->capacity * sizeof(row));
        if (!rows) {
            perror("Failed to allocate memory for rows");
            exit(EXIT_FAILURE);
        }
    }

    row *r = &rows[*num_rows];
    rows->content = malloc(strlen(content_in) + 1); // 分配内存
    r->content = strdup(content_in); // 复制内容
    if (!r->content) {
        perror("Failed to allocate memory for row content");
        exit(EXIT_FAILURE);
    }
    r->count = 1; // 初始行数为1
    r->lenth = strlen(content_in); // 设置长度
    (*num_rows)++;
}

void initialize_row(row *r) {
    r->content = NULL;
    r->count = 0;
    r->lenth = 0;
    r->capacity = INIT_CAPACITY; // 初始化容量
}