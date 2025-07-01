#ifndef EDITOR_IO_H
#define EDITOR_IO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 清除屏幕
#define CLEAR() printf("\033[2J")
// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))
// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))
// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))
// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))
// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")
//定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

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