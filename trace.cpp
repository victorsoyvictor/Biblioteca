/*
	Trace.h
*/

#ifndef __TRACE_H__
#define __TRACE_H__

//#include <crtdbg.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "DiskIO.h"
#include "Reloj.h"

#define TRACEMAXSTRING	1024

void registra (string salida, const char* format,...)
{
 if (salida == "")
     return;

 CReloj ahora;
 char szBuffer[TRACEMAXSTRING];
 va_list args;
 va_start(args,format);
 int nBuf;
 #ifdef __WIN32__
 nBuf = _vsnprintf(szBuffer,
                   TRACEMAXSTRING,
                   format,
                   args);
#endif
#ifdef __UNIX__
 nBuf = vsnprintf(szBuffer,
                   TRACEMAXSTRING,
                   format,
                   args);
#endif
 va_end(args);

 CArchivoTexto fsalida;
 if (fsalida.AbreArchivoSeguirEscritura(salida))
 {

     fsalida.GuardaTexto(ahora.fecha_y_hora());
     fsalida.GuardaTexto(":");
     fsalida.GuardaTexto("\n\n\t");
     fsalida.GuardaTexto(szBuffer);
     fsalida.GuardaTexto("\n\n");
     fsalida.CierraArchivo();
 }

}

#ifdef _DEBUG

char szBuffer[TRACEMAXSTRING];

void TRACE(const char* format,...)
{
 va_list args;
 va_start(args,format);
 int nBuf;
#ifdef __WIN32__
 nBuf = _vsnprintf(szBuffer,
                   TRACEMAXSTRING,
                   format,
                   args);
#endif
#ifdef __UNIX__
 nBuf = vsnprintf(szBuffer,
                   TRACEMAXSTRING,
                   format,
                   args);
#endif
 va_end(args);

 cout << szBuffer << endl;
}
#else
void TRACE(const char* format,...)
{
}

#endif


#endif // __TRACE_H__
