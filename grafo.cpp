/*
#include "grafo.h"
#include "Utiles.h"
#include <stdio.h>

using namespace std;

CGrafo::CGrafo(string nombre)
{
    m_archivografo = nombre;
    m_nodos = 0;
    m_grado = 0;
}

CGrafo::~CGrafo()
{
    unsigned int nodo;
    for (nodo = 0; nodo < MAX_BUFFER; nodo++)
     delete []m_buffer[nodo];

    delete []m_indice;
}

bool CGrafo::PreparaGrafo(unsigned int nodos, unsigned int grado, bool generaarchivo)
{
   unsigned int nodo,K;
   unsigned char * ceros = new unsigned char[grado*4];
   if (ceros == NULL)
     return false;
   
   if (!m_fgrafo.AbreArchivoLecturaEscritura(m_archivografo))
      return false;
   m_nodos = nodos;
   m_grado = grado;

   for (K = 0; K < grado*4; K++)
     ceros[K] = 0;

   m_indice = new unsigned int[nodos];
   if (m_indice == NULL)
       return false;

   if (generaarchivo == true)
     for (nodo = 0; nodo < nodos; nodo++)
     {
         m_indice[nodo] = 0;
         m_fgrafo.GuardaDatos(ceros,grado*4);
         cout << nodo;
         backline();
     }

   delete []ceros;

   for (nodo = 0; nodo < MAX_BUFFER; nodo++)
   {
     m_buffer[nodo] = new unsigned int[grado];
     if (m_buffer[nodo] == NULL)
        return false;
   }

   return true;
}

bool CGrafo::BuscaPosicionSegundoVertice(unsigned int nodoA,
										 unsigned int nodoB,
										 unsigned int &posicion,
										 bool &lleno,
										 bool &existe)
{
  if (nodoA < 1 || nodoA > m_nodos || nodoB < 1 || nodoB > m_nodos || m_nodos == 0)
    return false;

  unsigned int posnodo = (nodoA - 1) * (m_grado) * 4;
  unsigned int vecino = 0;
  unsigned char* pvecino = (unsigned char*) &vecino;
  unsigned int contador = 0;

  posicion = -1;

  do{
      if (m_fgrafo.LeeDatos(pvecino, 4, posnodo) == false)
          return false;
      posnodo += 4;
	  contador ++;
    } while (vecino != 0 && vecino != nodoB && contador < m_grado);

  posnodo -= 4;
  if (nodoB == vecino)
     existe = true;
  else
     existe  = false;
  
  if (vecino == 0)
	  lleno = false;
  else
	  lleno = true;
  
  posicion = posnodo;
  return true;
}

bool CGrafo::EstanConectados(unsigned int nodoA, unsigned int nodoB)
{
  unsigned int posicion = 0;
  bool lleno = 0;
  bool existe = 0;
  BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,lleno,existe);
  return existe;
}

bool CGrafo::GuardaAristaDoble(unsigned int nodoA, unsigned int nodoB)
{
   return (GuardaArista(nodoA,nodoB) && GuardaArista(nodoB,nodoA));
}

bool CGrafo::GuardaArista(unsigned int nodoA, unsigned int nodoB)
{
  unsigned int posicion = 0;
  bool lleno = 0;
  bool existe = 0;
  bool resultado = BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,lleno,existe);

  if (resultado == true && existe == false && lleno == false)
    return (m_fgrafo.GuardaDatos((unsigned char*)&nodoB,4,posicion));

  if (resultado == true && existe == true)
	  return true;

  return false;
}

unsigned int CGrafo::CuantosVecinos(unsigned int nodoA)
{
  if (nodoA < 1 || nodoA > m_nodos || m_nodos == 0)
    return false;

  return true;
}

unsigned int CGrafo::Vecino(unsigned int nodoA, unsigned int posicion)
{
  if (nodoA < 1 || nodoA > m_nodos || m_nodos == 0 || posicion > m_grado*2 || posicion < 1)
    return false;

  return true;
}

bool CGrafo::CompruebaAdyacencia(unsigned int nodoA, unsigned int nodoB)
{
  if (nodoA < 1 || nodoA > m_nodos || nodoB < 1 || nodoB > m_nodos || m_nodos == 0)
    return false;

  return true;
}
*/