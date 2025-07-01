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

  read_keyboard_input(rows, &num_rows);

  for(int j = 0; j < num_rows; j++) {
    print_row(&rows[j]);
  }
    return 0;
}