#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <menu.h>
#include "editor_io.h"



int show_menu() {
    int choice;

    printf("\033[36m");

    printf("\n========================\n");
    printf(">>> 系统 <<<\n");
    printf("========================\n");

    printf("\033[0m");
    printf("\033[32m");
    
    printf("0. 退出\n");
    printf("1. 写入\n");
    printf("2. 打印\n");
    printf("3. 屏幕清除\n");
    printf("4. 阅读模式\n");

    printf("\033[0m");
    printf("\033[36m");

    printf("========================\n");
    printf("请选择操作: ");

    printf("\033[0m");
    
    scanf("%d", &choice);
    return choice;
}

