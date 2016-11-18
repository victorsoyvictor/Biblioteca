/*
	aleatorio.h
*/

#ifndef __ALEATORIO_H__
#define __ALEATORIO_H__

#include <time.h>
#include <stdlib.h>
#include "definiciones.h"
#include "mprandom.h"

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

// http://www.robertnz.net/nr02doc.htm

/* random number generator of Park and Miller with Bays-Durham shuffle and added
safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint
values). Call with idum a negative integer to initialize; thereafter, do not alter idum between
successive deviates in a sequence. RNMX should approximate the largest floating value that is
less than 1.*/

class CRandomPMBD
{
public:
	CRandomPMBD();
	~CRandomPMBD();
	float operator()();
	int IntRnd(int min, int max);
	float Rnd();

private:
	long idum;
};

// Esta clase genera numeros aleatorios usando rand() de la biblioteca estandar
class CDado
{
public:
    CDado();
    void Inicia(void);
	BASE_TYPE Tira();
    // Devuelte un entero entre 1..max
    unsigned int TiraMaxInt(unsigned int max);
};

// Esta clase genera numeros aleatorios usando
// L'Ecuyer's 1996 Tausworthe generator taus88
class CDadoTAUS88
{
private:
    MATPACK::Ran088 *dado;

public:

    CDadoTAUS88(unsigned long inicializador);
    CDadoTAUS88();
    ~CDadoTAUS88();

    void Inicia(void);

    void Inicia(unsigned long inicializador);

    // Devuelte un float entre 0..1
	BASE_TYPE TiraFloat();

    // Devuelte un entero entre 0..4294967295U
    unsigned int TiraInt();

    // Devuelte un entero entre min..max
    unsigned int TiraRangoInt(unsigned int min, unsigned int max);

};

#endif // __ALEATORIO_H__
