#ifndef __GRAFOVIRTUAL_H__
#define __GRAFOVIRTUAL_H__

#include "DiskIO.h"
#include <string>

/* Esta clase almacena un grafo con un número determinado de nodos y grado en disco, y trabaja ocupando en memoria
   solo un buffer definido por MAX_BUFFER, permitiendo usar grafos de tamaño superior a la RAM a costa de un
   acceso mucho más lento*/
#define MAX_BUFFER 1024

using namespace std;

class CGrafoVirtual
{
public:
	CGrafoVirtual(string nombre);
	~CGrafoVirtual();
	bool PreparaGrafo(unsigned int nodos, unsigned int grado, bool generaarchivo);
	bool GuardaArista(unsigned int nodoA, unsigned int nodoB);
	bool GuardaAristaDoble(unsigned int nodoA, unsigned int nodoB);
	unsigned int CuantosVecinos(unsigned int nodoA);
	unsigned int Vecino(unsigned int nodoA, unsigned int posicion);
	bool CompruebaAdyacencia(unsigned int nodoA, unsigned int nodoB);
	bool EstanConectados(unsigned int nodoA, unsigned int nodoB);

private:
    CArchivoBinario m_fgrafo;
    string m_archivografo;
    unsigned int  m_nodos;
    unsigned int  m_grado;
	unsigned int* m_buffer[MAX_BUFFER];
	unsigned int* m_indice;
	bool BuscaPosicionSegundoVertice(unsigned int nodoA,
		                             unsigned int nodoB,
									 unsigned int &posicion,
									 bool &lleno,
									 bool &existe);



};

#endif
