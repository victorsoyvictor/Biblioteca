#ifndef __DISKIO_H__
#define __DISKIO_H__

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Utiles.h"

#ifdef __WIN32__
#include "dirent.h"
#endif

#ifdef __UNIX__
#include <dirent.h>
#endif

#include <time.h>
#include <string>
#include <vector>


using namespace std;

class CArchivoTexto
{
  public:
	CArchivoTexto();
	~CArchivoTexto();
	bool AbreArchivoLectura(string archivo);
	bool AbreArchivoEscritura(string archivo);
    bool AbreArchivoSeguirEscritura(string archivo);
	bool GuardaChar(char letra);
	bool GuardaTexto(string datos);
	bool GuardaTexto(int datos);
	bool GuardaTexto(unsigned int datos);
	bool GuardaTexto(BASE_TYPE datos);
	bool LeeTexto(string &buffer, unsigned int cantidad);
	bool LeeLinea(string &buffer);
	bool LeeLinea(unsigned int &entero);
	bool LeeLinea(BASE_TYPE &entero);
	bool LeePalabra(string &buffer);
	bool LeeArchivoCompleto(string &buffer);
	bool CierraArchivo();
	bool BorraArchivo();
    bool FinDeArchivo();

  private:
	 FILE *pArchivo;
	 string m_nombrearchivo;

};

class CArchivoBinario
{
  public:
	CArchivoBinario();
	~CArchivoBinario();
	bool AbreArchivoLectura(string archivo);
	bool AbreArchivoEscritura(string archivo);
	bool AbreArchivoLecturaEscritura(string archivo);
	bool GuardaDatos(string datos);
    bool GuardaDatos(unsigned char* datos, unsigned int longitud);
	bool GuardaDatos(unsigned char* datos, unsigned int longitud, unsigned int posicion);
	bool LeeDatos(string &buffer, unsigned int cantidad);
	bool LeeDatos(unsigned char *buffer, unsigned int cantidad);
	bool LeeDatos(unsigned char *buffer, unsigned int cantidad, unsigned int posicion);
	bool LeeArchivoCompleto(string &buffer);
	bool CierraArchivo();
	bool BorraArchivo();
    bool CierraArchivoYMarcaEjecutable();
    bool FinDeArchivo();

  private:
	 FILE *pArchivo;
	 string m_nombrearchivo;

};

#define ES_ARCHIVO		0
#define ES_DIRECTORIO	1
class CDirectorio
{

public:
   CDirectorio();
   ~CDirectorio();
   bool LeeDirectorio(string ruta);
   string Entrada(unsigned int entrada);
   string Nombre(unsigned int entrada);
   string NombreCompleto(unsigned int entrada);
   string RutaNombre(unsigned int entrada);
   string Extension(unsigned int entrada);
   time_t Antiguedad(unsigned int entrada);
   bool ActualizaHora(unsigned int entrada);
   bool ActualizaHora(string nombrearchivo);
   void dump();
   unsigned int Entradas();
   int ExisteEntrada(string nombrearchivo);
   string BuscaPrimeroConExtension(string extension);
   string BuscaRutaPrimeroConExtension(string extension);
   bool Renombra(string nuevonombre,unsigned int entrada);
   bool Renombra(string nuevonombre,string viejonombre);
   bool CambiaExtension(string nuevaextension,unsigned int entrada);
   bool CambiaExtension(string nuevaextension, string nombrearchivo);
   void Actualiza();
   unsigned int CuentaArchivos(string extension);
   bool BorraArchivo(unsigned int entrada);
   unsigned int BorraArchivoPorNombre(string nombre, string extension);
   bool MueveArchivo(unsigned int entrada, string destino);
   bool CopiaArchivo(unsigned int entrada, string destino);
   bool CopiaArchivo(string origen, string destino);
   unsigned int MueveArchivosPorExtension(string extension, string destino);
   bool EsDirectorio(unsigned int entrada);
   CDirectorio EntraEnDirectorio(unsigned int entrada);
   string NombreDirectorio();

private:
   vector<string> directorio;
   vector<int>    tipo_entrada;
   unsigned int entradas;
   string ruta_de_acceso;

};

class CCRC
{

public:
   CCRC();
   ~CCRC();
   virtual unsigned int CalculaCRC(string cadena);
   virtual bool CompruebaCRC(string cadena);
   virtual string InsertaCRC(string &cadena);
   virtual unsigned int LargoCRC();
private:
   unsigned char CRC;
};

class CCRC32:public CCRC
{
public:
   CCRC32();
   ~CCRC32();

   unsigned int CalculaCRC(string cadena);
   string       CalculaCRCASCII(string cadena);

   bool         CompruebaCRC(string cadena);
   bool         CompruebaCRCASCII(string cadena);

   string       InsertaCRC(string &cadena);
   string       InsertaCRCASCII(string &cadena);

   unsigned int LargoCRC();
   unsigned int LargoCRCASCII();

private:   
   unsigned int CRC;
   string       CRCASCII;
};

#endif
