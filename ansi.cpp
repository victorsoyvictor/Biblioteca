#include "ansi.h"
#ifdef __UNIX__

struct termios oldterm, newterm;
void set_unbuffered ( void ) {
  tcgetattr( STDIN_FILENO, &oldterm );
  newterm = oldterm;
  newterm.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newterm );
}
void set_buffered ( void ) {
  tcsetattr( STDIN_FILENO, TCSANOW, &oldterm );
}

int kbhit ( void ) {
    int result;
    fd_set  set;
    struct timeval tv;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO,&set);  /* watch stdin */
    tv.tv_sec = 0;
    tv.tv_usec = 0;             /* don't wait */

    /* quick peek at the input, to see if anything is there */
    set_unbuffered();
    result = select( STDIN_FILENO+1,&set,NULL,NULL,&tv);
    set_buffered();

    return result == 1;
}

int getch(void)
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


#endif

#ifdef __WIN32__

  void gotoxy(int x, int y)
  {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  }
#endif

