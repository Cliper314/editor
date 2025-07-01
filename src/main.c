#include <stdio.h>
#include <ctype.h>
#include "editor.h"
#include "editor_io.h"
#include "menu.h"

int x = 0, y = 0;

int main(int argc,char *argv[]) {
  int i =0;
  char tem_row[MAX_LENGTH];
  row rows[INIT_CAPACITY];
  int num_rows = 0;
  for (int i = 0; i < INIT_CAPACITY; i++) {
    initialize_row(&rows[i]);
  }
  while(1){
    int choice = show_menu();
    switch (choice)
    {
    case 0:
     for (int j = 0; j < num_rows; j++) {
      free(rows[j].content);
   }
      printf("退出程序\n");
      return 0;
   case 1:
      enableRawMode();//进入原始模式
      char c;
      read_keyboard_input(rows, &num_rows, x, y);
      disableRawMode(); 
      CLEAR();
      break;
  
    case 2:
      for(int j = 0; j < num_rows; j++) {

        print_row(&rows[j]);
      }
      break;

    case 3:
      CLEAR();
      break;
    case 4:
      for(int j = 0; j < num_rows; j++) {

         print(&rows[j]);
        }
        enableRawMode();
     //while(1){
      read_mode();  
      SHOW_CURSOR();
      MOVETO(x, y);
      CLEAR();
      disableRawMode();
    //}
      break;
    default:
      break;
   }
}

  
  CLEAR();
  // 释放内存
  for (int j = 0; j < num_rows; j++) {
    free(rows[j].content);
  }
    return 0;
}