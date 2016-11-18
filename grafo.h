#ifndef __GRAFO_H__
#define __GRAFO_H__

#define NO_CHECK
#define INT18
//#define USA_LISTA

#include "DiskIO.h"
#include <string>
#include <vector>
#include <list>
using namespace std;

#ifdef INT18
class  UINT18
{
    public:
    unsigned char LOW;
    unsigned char MED;
    unsigned char HIGH;
	UINT18(unsigned int valor)
	{
		*this = valor;
	}
    void operator=(unsigned int valor)
    {
        LOW = (valor & 0x000000FF);
        MED = (valor & 0x0000FF00) / 0x100;
        HIGH = (valor & 0x00FF0000) / 0x10000;
    }

    operator unsigned int()
    {
      unsigned int x;
      x = LOW + MED*256 + HIGH*256*256;
      return x;
    }

    void operator=(UINT18 valor)
    {
      LOW = valor.LOW;
      MED = valor.MED;
      HIGH = valor.HIGH;
    }
};

#endif

template <class T>
class CGrafo
{
public:

	// Genera el grafo inicializando el vector de nodos y la lista de adyacencia
	CGrafo(string nombre = "NO DEFINIDO", unsigned int nodos = 0)
	{
	  Inicia(nombre, nodos);
	}


    void Inicia(string nombre, unsigned int nodos)
	{
	  m_nombre = nombre;
      m_numnodos = nodos;
      m_numero_de_aristas = 0;
      m_nodos.erase(m_nodos.begin(),m_nodos.end());
	  m_nodos.resize(m_numnodos);
	  m_adyacencias.erase(m_adyacencias.begin(),
                          m_adyacencias.end());
	  m_adyacencias.resize(m_numnodos);
	}

	// no requerido
	~CGrafo()
	{

	}

    // devuelve un nodo de una posicion determinada
    T& Nodo(unsigned int posicion)
    {
      if (posicion > m_numnodos)
          return m_nodo_omision;
      else
          return m_nodos[posicion];
    }

	//guarda un nodo en una posición determinada del vector de nodos
	bool GuardaNodo(T nodo, unsigned int posicion)
	{
		if (posicion >= m_numnodos)
			return false;

		m_nodos[posicion] = nodo;
		return true;
	}

	//mira si el nodoA tiene en su lista de adyacencia al nodoB, y devuelve en qué posición
	bool BuscaPosicionSegundoVertice(unsigned int nodoA,
									 unsigned int nodoB,
									 unsigned int &posicion,
									 bool &existe)
	{
      unsigned int pos = 0;
#ifndef NO_CHECK
	  if (nodoA >= m_numnodos || nodoB >= m_numnodos || m_numnodos == 0)
		return false;
#endif

#ifdef USA_LISTA
      list<unsigned int>::iterator vecino = m_adyacencias[nodoA].begin();
      for ( pos = 0;
            vecino != m_adyacencias[nodoA].end();
            vecino++, pos++)
      {
         if (*vecino == nodoB)
#else
	  for ( pos = 0; pos < m_adyacencias[nodoA].size();pos++)
	  {
         if (m_adyacencias[nodoA][pos] == nodoB)
#endif
		 {

			 existe = true;
			 posicion = pos;
			 return true;
		 }
	  }
	  existe = false;
	  posicion = pos;
	  return true;
	}

	//conecta nodoA con nodoB en la lista de adyacencia
	bool GuardaArista(unsigned int nodoA, unsigned int nodoB)
	{
	  bool existe = false;
	  unsigned int posicion = 0;

	  bool resultado = BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,existe);

	  if (resultado == true && existe == false)
	  {
		 m_adyacencias[nodoA].push_back(nodoB);
         m_numero_de_aristas++;
		 return true;
	  }

	  if (resultado == true && existe == true)
		  return true;

	  return false;
	}
	//desconecta nodoA con nodoB en la lista de adyacencia
	bool BorraArista(unsigned int nodoA, unsigned int nodoB)
	{
	  bool existe = false;
	  unsigned int posicion = 0;

	  bool resultado = BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,existe);

	  if (resultado == true && existe == true)
	  {
		 m_adyacencias[nodoA].erase( m_adyacencias[nodoA].begin() + posicion);
         m_numero_de_aristas--;
		 return true;
	  }

	  if (resultado == true && existe == false)
		  return true;

	  return false;
	}

	//indica si dos nodos están conectados
	bool EstanConectados(unsigned int nodoA, unsigned int nodoB)
	{
	  unsigned int posicion = 0;
	  bool existe = 0;
	  BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,existe);
	  return existe;
	}

	//conecta nodoA con nodoB y viceversa
	bool GuardaAristaDoble(unsigned int nodoA, unsigned int nodoB, bool doblecheck = false)
	{
	   //
      bool existe = false;
	  unsigned int posicion = 0;

      if (doblecheck == true)
      {  // comprueba que no existe ni la arista en sentido A->B ni la arista en sentido B->A
         return (GuardaArista(nodoA,nodoB) && GuardaArista(nodoB,nodoA));
      }
      else
      {
        //solo comprueba si existe la arista A->B, si no existe asume que tampoco existe B->A
        //esto se hace para ahorrarse la mitad de las búsquedas
	     bool resultado = BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,existe);
	     if (resultado == true && existe == false)
	      {
		     m_adyacencias[nodoA].push_back(nodoB);
             m_adyacencias[nodoB].push_back(nodoA);
             m_numero_de_aristas++;
             m_numero_de_aristas++;
		     return true;
	      }

	      if (resultado == true && existe == true)
		      return false;
      }

	  return false;
	}

	//conecta nodoA con nodoB y viceversa
	bool BorraAristaDoble(unsigned int nodoA, unsigned int nodoB, bool doblecheck = false)
	{
	   //
      bool existe = false;
	  unsigned int posicion = 0;

      if (doblecheck == true)
      {  // comprueba que no existe ni la arista en sentido A->B ni la arista en sentido B->A
         return (BorraArista(nodoA,nodoB) && BorraArista(nodoB,nodoA));
      }
      else
      {
        //solo comprueba si existe la arista A->B, si no existe asume que tampoco existe B->A
        //esto se hace para ahorrarse la mitad de las búsquedas
	     bool resultado = BuscaPosicionSegundoVertice(nodoA,nodoB,posicion,existe);
         if (resultado == true && existe == true)
          {
            m_adyacencias[nodoA].erase(m_adyacencias[nodoA].begin() + posicion);
            m_numero_de_aristas--;
            resultado = BuscaPosicionSegundoVertice(nodoB,nodoA,posicion,existe);
            if (resultado == true && existe == true)
            {
                m_adyacencias[nodoB].erase(m_adyacencias[nodoB].begin() + posicion);
                m_numero_de_aristas--;
            }
            return true;
          }

          if (resultado == true && existe == false)
              return true;
      }

	  return false;
	}



	//devuelve cuantos vecinos tiene un nodo
	unsigned int CuantosVecinos(unsigned int nodoA)
	{
#ifndef NO_CHECK
	  if (nodoA >= m_numnodos || m_numnodos == 0)
		return 0;
#endif

	  return (unsigned int) m_adyacencias[nodoA].size();
	}

	//devuelve qué vecino de nodoA está en una posición determinada de su lista de adyacencia
	unsigned int Vecino(unsigned int nodoA, unsigned int posicion)
	{
#ifndef NO_CHECK
	  if (nodoA >= m_numnodos || m_numnodos == 0)
		return 0;

	  if (m_adyacencias[nodoA].size() <= posicion)
		  return 0;
#endif
#ifdef USA_LISTA
      list<unsigned int>::iterator vecino = m_adyacencias[nodoA].begin();
      unsigned int posvecino = 0;
      for ( posvecino = 0; posvecino < posicion; posvecino++)
          vecino++;
      return *vecino;
#else
      return m_adyacencias[nodoA][posicion];
#endif

	}

    //devuelve qué vecino de nodoA está en una posición determinada de su lista de adyacencia
    T& NodoVecino(unsigned int nodoA, unsigned int posicion)
	{
#ifndef NO_CHECK
	  if (nodoA >= m_numnodos || m_numnodos == 0)
		return m_nodo_omision;

	  if (m_adyacencias[nodoA].size() <= posicion)
		  return m_nodo_omision;
#endif
#ifdef USA_LISTA
      list<unsigned int>::iterator vecino = m_adyacencias[nodoA].begin();
      unsigned int posvecino = 0;
      for ( posvecino = 0; posvecino < posicion; posvecino++)
          vecino++;
      return m_nodos[*vecino];

#else
	  return m_nodos[m_adyacencias[nodoA][posicion]];
#endif
	}

    unsigned int  m_numnodos;
    unsigned int  m_numero_de_aristas;
	string                         m_nombre;

    //private:
	vector< T >                    m_nodos;
#ifdef USA_LISTA
	vector< list<unsigned int> >   m_adyacencias;
#else
	vector< vector<
#ifdef INT18
        UINT18
#else
		unsigned int
#endif
	> >  m_adyacencias;
#endif
    T                              m_nodo_omision;

};

#endif
