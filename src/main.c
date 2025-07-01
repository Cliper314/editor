#include <stdio.h>
#include <ctype.h>
#include "editor.h"

int main(int argc,char *argv[]) {
    enableRawMode();//进入原始模式
    char c;
    while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1) die("read");
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }
    return 0;
}