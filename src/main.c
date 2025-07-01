#include <stdio.h>
#include <ctype.h>
#include "editor.h"
#include "editor_io.h"

int main(int argc,char *argv[]) {
  int i =0;
  char tem_row[MAX_LENGTH];
  row rows[20];
  int num_rows = 0;
  for (int i = 0; i < INIT_CAPACITY; i++) {
    initialize_row(&rows[i]);
  }
  enableRawMode();//进入原始模式
  char c;


  while (1) {
  char c = '\0';
  if (read(STDIN_FILENO, &c, 1) == -1) die("read");
  if (iscntrl(c)) {
    printf("%d", c);
  } else {
    printf("%d ('%c')", c, c);
  }
  fflush(stdout);
  if(c != '\n') {
    tem_row[i++] = c; // 将输入字符添加到临时行
  }
  else {
    tem_row[i] = '\0'; // 结束字符串
    i = 0;
    //printf("Adding new line: %s\n", tem_row);
    add_row(rows, &num_rows, tem_row); // 添加行到rows
    //printf("New line added.\n");
    //printf("Current rows: %s\n", rows[num_rows-1].content);
  }
  if (c == 'q') break;
  }

  for(int j = 0; j < num_rows; j++) {
    print_row(&rows[j]);
  }
    return 0;
}