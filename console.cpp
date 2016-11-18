/*
 * NOTA: En los comentarios de este fichero se han eliminado las tildes y las 
 * enies porque se ha comprobado que dan problemas de compilacion. Estos proble-
 * mas son solucionables eligiendo un juego de caracteres adecuados, pero para
 * simplificar preferimos dejarlo asi y no complicar mas el asunto.
 * 
 * CONSOLE.cpp
 * Implementacion de las funciones listadas en console.h
 */ 

#include <iostream>
#include "console.h"
using namespace std;

/* ============ FUNCION ============ */

void clrscr()
{
#ifdef __UNIX__
	system ("clear");
#endif
#ifdef __WIN32__
	system ("cls");
#endif

}

void gotoxy (int x, int y)
{
#ifdef __UNIX__
	printf("%c[%d;%df",0x1B,y,x);
#endif
#ifdef __WIN32__
   COORD coord; 
   coord.X = x; 
   coord.Y = y; 
   SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), coord); 
#endif
} 


void set_color(t_color color)
{
#ifdef __UNIX__
#endif
#ifdef __WIN32__
   switch (color)
   {
      case E_WHITE_ON_BLACK:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_RED |
                                 FOREGROUND_GREEN | FOREGROUND_BLUE);
         break;
      case E_RED_ON_BLACK:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_RED);
         break;
      case E_GREEN_ON_BLACK:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_GREEN);
         break;
      case E_YELLOW_ON_BLACK:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_RED |
                                 FOREGROUND_GREEN);
         break;
      case E_BLUE_ON_BLACK: 
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_BLUE);
         break;
      case E_MAGENTA_ON_BLACK:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_RED |
                                 FOREGROUND_BLUE);
         break;
      case E_CYAN_ON_BLACK:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_GREEN |
                                 FOREGROUND_BLUE);
         break;
      case E_BLACK_ON_GRAY:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
         break;
      case E_BLACK_ON_WHITE:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE);
         break;
      case E_RED_ON_WHITE:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE |
                                 FOREGROUND_RED);
         break;
      case E_GREEN_ON_WHITE:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE | FOREGROUND_GREEN);
         break;
      case E_YELLOW_ON_WHITE:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE | FOREGROUND_RED |
                                 FOREGROUND_GREEN);
         break;
      case E_BLUE_ON_WHITE: // Blue on White
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE | FOREGROUND_BLUE);
         break;
      case E_MAGENTA_ON_WHITE: // Magenta on White
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE | FOREGROUND_RED |
                                 FOREGROUND_BLUE);
         break;
      case E_CYAN_ON_WHITE:
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE | FOREGROUND_GREEN |
                                 FOREGROUND_BLUE);
         break;
      case E_WHITE_ON_WHITE: // White on White
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                                 BACKGROUND_RED | BACKGROUND_GREEN |
                                 BACKGROUND_BLUE | FOREGROUND_RED |
                                 FOREGROUND_GREEN | FOREGROUND_BLUE);
         break;
      default : // White on Black
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 FOREGROUND_INTENSITY | FOREGROUND_RED |
                                 FOREGROUND_GREEN | FOREGROUND_BLUE);
         break;
   }
#endif
}  


// Fin del fichero console.cpp
