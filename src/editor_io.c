#include "editor_io.h"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

extern int x, y;

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

void print_row(const row *r) {
    if (r->content) {
        printf("Row content: %s\n", r->content);
        printf("Row capacity: %d\n", r->capacity);
    } else {
        printf("Row is empty.\n");
    }
    return;
}

void print(const row *r) {
    if (r->content) {
        printf("Row %d: %s\n", r->count, r->content);
    } else {
        printf("Row is empty.\n");
    }
    return;
}

void initialize_row(row *r) {
    r->content = NULL;
    r->count = 0;
    r->lenth = 0;
    r->capacity = INIT_CAPACITY; // 初始化容量
}

void read_keyboard_input(row *rows, int *num_rows,int x, int y) {
    char c;
    char tem_row[MAX_LENGTH];
    int i = 0;
    int a = 0, b = 0;

    while (1) {
        if (read(STDIN_FILENO, &c, 1) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (c == 27) {
            if (read(STDIN_FILENO, &c, 1) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            else if (c == '[') {
                if (read(STDIN_FILENO, &c, 1) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("Escaped character detected: %d\n", c);
            }

            switch (c) {
            case 'A':printf("Up arrow detected\n");
                    break;
            case 'B':printf("Down arrow detected\n");
                    break;
            case 'C':printf("Right arrow detected\n");
                    break;
            case 'D':printf("Left arrow detected\n");
                    break;
            case 'F':printf("End key detected\n");break;
            case 'H':printf("Home key detected\n");break;
            case 53:if(read(STDIN_FILENO, &c, 1) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (c == '~')
                    printf("Page Up key detected\n");break;
            case 54:if(read(STDIN_FILENO, &c, 1) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (c == '~') 
                    printf("Page Down key detected\n");break;
            default:printf("Unknown escape sequence: %d\n", c);
            }
            continue; // 跳过控制字符
            
        }

        if (iscntrl(c)) {
            printf("%d", c);
        } else {
            printf("%d ('%c')", c, c);
        }
        fflush(stdout);

        if (c != '\n') {
            tem_row[i++] = c; // 将输入字符添加到临时行
        } else {
            tem_row[i] = '\0'; // 结束字符串
            i = 0;
            add_row(rows, num_rows, tem_row); // 添加行到rows
        }

        if (c == 'q') break; // 退出条件
    }
    
}

void read_mode() {
    char c;

    while (1) {
        fflush(stdout);
        
        if (read(STDIN_FILENO, &c, 1) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (c == 27) {
            if (read(STDIN_FILENO, &c, 1) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            else if (c == '[') {
                if (read(STDIN_FILENO, &c, 1) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("Escaped character detected: %d\n", c);
            }

            switch (c) {
            case 'A'://printf("Up arrow detected\n");
                    //y += 1;
                    MOVEUP(x);break;
            case 'B'://printf("Down arrow detected\n");
                    //y -= 1;
                    MOVEDOWN(x);break;
            case 'C'://printf("Right arrow detected\n");
                    //x += 1;
                    MOVERIGHT(y);break;
            case 'D'://printf("Left arrow detected\n");
                    //x -= 1;
                    MOVELEFT(y);break;
            case 'F'://printf("End key detected\n");
                return;
            break;
            case 'H'://printf("Home key detected\n");
            break;
            case 53:if(read(STDIN_FILENO, &c, 1) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (c == '~')
                    //printf("Page Up key detected\n");
                    system("more");
                    break;
            case 54:if(read(STDIN_FILENO, &c, 1) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                if (c == '~') 
                    //printf("Page Down key detected\n");
                    break;
            }
            continue; // 跳过控制字符
            
        }

    }
}