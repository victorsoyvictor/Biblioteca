/*
 * NOTA: En los comentarios de este fichero se han eliminado las tildes y las 
 * enies porque se ha comprobado que dan problemas de compilacion. Estos proble-
 * mas son solucionables eligiendo un juego de caracteres adecuados, pero para
 * simplificar preferimos dejarlo asi y no complicar mas el asunto.
 *  
 * CONSOLE.H
 * Fichero con funciones para el manejo de la ventana de comandos.
 * Incluye funciones para controlar el tamanio de la ventana y algunas posibili-
 * dades relacionadas con el color del texto de salida.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdlib.h>
#include <stdio.h>
#ifdef __UNIX__

#endif
#ifdef __WIN32__
#include <windows.h>
#endif


typedef enum { E_WHITE_ON_BLACK,  E_RED_ON_BLACK,     E_GREEN_ON_BLACK,
               E_YELLOW_ON_BLACK, E_BLUE_ON_BLACK,    E_MAGENTA_ON_BLACK, 
               E_CYAN_ON_BLACK,   E_BLACK_ON_GRAY,    E_BLACK_ON_WHITE,
               E_RED_ON_WHITE,    E_GREEN_ON_WHITE,   E_YELLOW_ON_WHITE,
               E_BLUE_ON_WHITE,   E_MAGENTA_ON_WHITE, E_CYAN_ON_WHITE,
               E_WHITE_ON_WHITE} t_color;

void clrscr();
void gotoxy (int x, int y);
void set_color (t_color color);

#endif
// Fin fichero console.h
