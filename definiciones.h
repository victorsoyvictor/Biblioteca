#ifndef _DEFINICIONES_
#define _DEFINICIONES_

#define BASE_TYPE long double
#define PI 3.14159265358979323846264338328
#define NUMERO_E 2.7182818284590452353602875
#define BYTE_TYPE unsigned char
#define wait() {while ('\n' != getchar());}
#define ARCHIVO_WATCHDOG "watchdog.txt"
#define ARCHIVO_PROGRESO "progreso.txt"
#define ARCHIVO_DEBUG "debug.txt"
#ifdef __UNIX__
  #define FALSE false
  #define TRUE true
#endif
#endif
