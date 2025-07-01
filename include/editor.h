#ifndef EDITOR_H
#define EDITOR_H
#include <unistd.h>
#include <sys/syscall.h>
#include <termios.h>

void enableRawMode();
void disableRawMode();

#endif