/*
	Trace.h
*/

#ifndef __TRACE_H__
#define __TRACE_H__

//#include <crtdbg.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>

using namespace std;

void registra (string salida, const char* format,...);

void TRACE(const char* format,...);

#endif // __TRACE_H__
