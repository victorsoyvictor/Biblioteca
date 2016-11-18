#ifndef ANSICOLOR_H
#define ANSICOLOR_H

//Comentar la que no proceda

#include <stdlib.h>
#include <stdio.h>

typedef enum { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE } color_t;

#ifdef __UNIX__
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
  #define set_fcolor(color) printf("\e[3%dm", color)
  #define set_bcolor(color) printf("\e[4%dm", color)
  #define clrscr()          printf("\e[2J")
  //o system ("clear");
  #define gotoxy(x, y)      printf("\e[%d;%df", y, x)
  #define high_mode()       printf("\e[Bm")
  #define reverse_mode()    printf("\e[rm")
  #define default_mode()    printf("\e[m")
  #define blink_mode()      printf("\e[km")

void set_unbuffered ( void );
void set_buffered ( void );
int kbhit ( void );
int getch(void);

#endif

#ifdef __WIN32__
  #include <conio.h>
  #include <windows.h>
  #define clrscr()          system ("cls")

  void gotoxy(int x, int y);
#endif

#endif //ANSICOLOR_H
