#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "definiciones.h"
#include <iomanip>
#include "DiskIO.h"
#include <limits>
#include <cmath>


#define PRECISION 17
using namespace std;




string entero_a_texto (int n) {

   ostringstream format_message;
   format_message << n;
   return format_message.str();
}

string entero_a_texto (unsigned int n) {

   ostringstream format_message;
   format_message << n;
   return format_message.str();
}

BASE_TYPE texto_a_TipoBase(const string& s)
 {
   istringstream i(s);
   BASE_TYPE x = 0.0;

   //if (!(i >> setprecision(20) >> x))
   //cout << numeric_limits<BASE_TYPE>::digits10 + 1;
   if (!(i >> setprecision(PRECISION) >> x))
   {
     cout << "Error convirtiendo texto a tipo base" << endl;
     //wait();
     exit(-1);
   }
   return x;
 }


 string TipoBase_a_texto(BASE_TYPE &x)
 {
   ostringstream format_message;
   if (sizeof(BASE_TYPE) <= 12)
     format_message << setprecision(PRECISION) << x;
   else
     format_message << setprecision(PRECISION) << (double)x;
   return format_message.str();
 }

int texto_a_entero(const string& s)
{
    return atol(s.c_str());
}

void backline(void)
{
    cout << (char) 13 << std::flush;
}

bool TRAZA(string texto)
{

    CArchivoTexto archivo;
    if (archivo.AbreArchivoSeguirEscritura(ARCHIVO_DEBUG) == false)
        return false;
    else
    {
        archivo.GuardaTexto(texto);
    }
    archivo.CierraArchivo();
    return true;
}

bool TRAZA(string nombre, string texto)
{

    CArchivoTexto archivo;
    if (archivo.AbreArchivoSeguirEscritura(nombre + ".txt") == false)
        return false;
    else
    {
        archivo.GuardaTexto(texto);
    }
    archivo.CierraArchivo();
    return true;
}

bool sigue_vivo()
{
    CArchivoTexto archivo;

    if (archivo.AbreArchivoLectura(ARCHIVO_WATCHDOG) == false)
        return false;
    else
    {
        archivo.CierraArchivo();
        archivo.BorraArchivo();
        return true;
    }
}

void colea()
{
    CArchivoTexto archivo;

    archivo.AbreArchivoEscritura(ARCHIVO_WATCHDOG);
    archivo.CierraArchivo();
}

void progreso(BASE_TYPE porcentaje)
{
    CArchivoTexto archivo;

    archivo.AbreArchivoEscritura(ARCHIVO_PROGRESO);
    archivo.GuardaTexto(TipoBase_a_texto(porcentaje));
    archivo.CierraArchivo();
}

string ConvierteBYTEaHex(unsigned char byte)
{
    string cadena = "00";
    unsigned char low =  byte & 0x0F;
    unsigned char high = byte/0x10;
    switch(high)
    {
    case 0:cadena = "0";
           break;
    case 1:cadena = "1";
           break;
    case 2:cadena = "2";
           break;
    case 3:cadena = "3";
           break;
    case 4:cadena = "4";
           break;
    case 5:cadena = "5";
           break;
    case 6:cadena = "6";
           break;
    case 7:cadena = "7";
           break;
    case 8:cadena = "8";
           break;
    case 9:cadena = "9";
           break;
    case 10:cadena = "A";
           break;
    case 11:cadena = "B";
           break;
    case 12:cadena = "C";
           break;
    case 13:cadena = "D";
           break;
    case 14:cadena = "E";
           break;
    case 15:cadena = "F";
           break;
    }

    switch(low)
    {
    case 0:cadena += "0";
           break;
    case 1:cadena += "1";
           break;
    case 2:cadena += "2";
           break;
    case 3:cadena += "3";
           break;
    case 4:cadena += "4";
           break;
    case 5:cadena += "5";
           break;
    case 6:cadena += "6";
           break;
    case 7:cadena += "7";
           break;
    case 8:cadena += "8";
           break;
    case 9:cadena += "9";
           break;
    case 10:cadena += "A";
           break;
    case 11:cadena += "B";
           break;
    case 12:cadena += "C";
           break;
    case 13:cadena += "D";
           break;
    case 14:cadena += "E";
           break;
    case 15:cadena += "F";
           break;
    }
    return cadena;
}

unsigned char ConvierteHexaBYTE(string cadena)
{
    unsigned char byte = 0;
    if (cadena.length() != 2)
        return 0;

    switch(cadena[1])
    {
    case '0':byte += 0;
             break;
    case '1':byte += 1;
             break;
    case '2':byte += 2;
             break;
    case '3':byte += 3;
             break;
    case '4':byte += 4;
             break;
    case '5':byte += 5;
             break;
    case '6':byte += 6;
             break;
    case '7':byte += 7;
             break;
    case '8':byte += 8;
             break;
    case '9':byte += 9;
             break;
    case 'A':
    case 'a':
             byte += 10;
             break;
    case 'B':
    case 'b':
             byte += 11;
             break;
    case 'C':
    case 'c':byte += 12;
             break;
    case 'D':
    case 'd':byte += 13;
             break;
    case 'E':
    case 'e':byte += 14;
             break;
    case 'F':
    case 'f':byte += 15;
             break;
    }

    switch(cadena[0])
    {
    case '0':byte += 0;
             break;
    case '1':byte += 1*0x10;
             break;
    case '2':byte += 2*0x10;
             break;
    case '3':byte += 3*0x10;
             break;
    case '4':byte += 4*0x10;
             break;
    case '5':byte += 5*0x10;
             break;
    case '6':byte += 6*0x10;
             break;
    case '7':byte += 7*0x10;
             break;
    case '8':byte += 8*0x10;
             break;
    case '9':byte += 9*0x10;
             break;
    case 'A':
    case 'a':
             byte += 10*0x10;
             break;
    case 'B':
    case 'b':
             byte += 11*0x10;
             break;
    case 'C':
    case 'c':byte += 12*0x10;
             break;
    case 'D':
    case 'd':byte += 13*0x10;
             break;
    case 'E':
    case 'e':byte += 14*0x10;
             break;
    case 'F':
    case 'f':byte += 15*0x10;
             break;
    }


    return byte;
}

string ConvierteUINTaHexString(unsigned int valor)
{
  string cadena = "";
  unsigned char byte1,byte2,byte3,byte4 = 0;

  byte4  = (valor/0x1000000) & 0x000000FF;
  cadena += ConvierteBYTEaHex(byte4);
  byte3  = (valor/0x10000)   & 0x000000FF;
  cadena += ConvierteBYTEaHex(byte3);
  byte2  = (valor/0x100)     & 0x000000FF;
  cadena += ConvierteBYTEaHex(byte2);
  byte1  = valor             & 0x000000FF;
  cadena += ConvierteBYTEaHex(byte1);

  return cadena;
}

unsigned int ConvierteHexStringaUINT(string cadena)
{
    unsigned int valor = 0;
    unsigned char byte1,byte2,byte3,byte4 = 0;
    if (cadena.length()<8)
        return 0;
    byte1 = ConvierteHexaBYTE(cadena.substr(6,2));
    byte2 = ConvierteHexaBYTE(cadena.substr(4,2));
    byte3 = ConvierteHexaBYTE(cadena.substr(2,2));
    byte4 = ConvierteHexaBYTE(cadena.substr(0,2));
    valor = byte4*0x1000000 + byte3*0x10000 + byte2*0x100 + byte1;
    return valor;
}

string porcentaje(BASE_TYPE origen, BASE_TYPE actual, BASE_TYPE destino)
{
    BASE_TYPE rango = destino - origen;
    BASE_TYPE pos   = actual - origen;

    BASE_TYPE porcentaje = 100.0*pos/rango;

    return entero_a_texto((unsigned int)porcentaje) + "%";
}

int fecha_a_meses(int year, int month)
{
	int mes = (year - 1900) * 12 + month;
	return mes;
}

void meses_a_fecha(int &year, int &mes, int meses)
{
	year = meses / 12;
	mes = meses % 12;
}

string meses_a_string(int meses)
{
	string valor;

	int year;
	int mes;
	meses_a_fecha(year,mes,meses);
	valor = entero_a_texto(year) + "/" + entero_a_texto(meses);
	return valor;
}

BASE_TYPE Lineal_Logaritmico(BASE_TYPE valor, BASE_TYPE minimo, BASE_TYPE maximo)
{
	if (valor <= 0)
		valor = 1;
	if (minimo <= 0)
		minimo = 1;
	if (maximo <= 0)
		maximo = 1;

	BASE_TYPE divisor = (log(maximo)-log(minimo));
	if (divisor == 0)
		return 0;
	else
	  return (log(valor)-log(minimo)) / divisor;

}
