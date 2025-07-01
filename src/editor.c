#include <unistd.h>
#include <sys/syscall.h>
#include <termios.h>


void die(const char *s) {
  perror(s);
  exit(1);
}

struct termios orig_termios;
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;//复制后进行后续操作
//超时设置
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 10;
//设置原始模式
  raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");//设置
}