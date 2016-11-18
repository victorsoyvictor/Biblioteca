#ifndef __INTVECTORZIP_H__
#define __INTVECTORZIP_H__

#include <iostream>
#ifdef __WIN32__
#include <tchar.h>
#endif
#ifdef __UNIX__
//#include <tchar.h>
#endif
#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <vector>

#include "stringzip.h"
using namespace std;


class CIntVectorZip
{
    private:

    CStringZip compresor;

    public:

std::string comprime(const std::vector<unsigned int>& valores)
{
    string entrada;
    string salida;
    int x;

    for (x= 0; x < valores.size(); x++)
    {
        int valor = valores[x];
        entrada.push_back((unsigned char) valor);
        entrada.push_back((unsigned char) (valor>>=8));
        entrada.push_back((unsigned char) (valor>>=8));
        entrada.push_back((unsigned char) (valor>>=8));
    }

    salida = compresor.comprime(entrada);

    return salida;
}

/** Decompress an STL string using zlib and return the original data. */
std::vector<unsigned int> descomprime(const std::string& cadena)
{
    string entrada;
    vector<unsigned int> salida;
    int x;
    unsigned int valor = 0;

	if (cadena.length() == 0)
		return salida;

    entrada = compresor.descomprime(cadena);

    for (x= 0; x < entrada.length(); )
    {
        unsigned char byte1 = entrada[x++];
        unsigned char byte2 = entrada[x++];
        unsigned char byte3 = entrada[x++];
        unsigned char byte4 = entrada[x++];
        valor = 0;
        valor = (valor << 8) + byte4;
        valor = (valor << 8) + byte3;
        valor = (valor << 8) + byte2;
        valor = (valor << 8) + byte1;
        salida.push_back(valor);
    }
    return salida;
}

};

#endif
