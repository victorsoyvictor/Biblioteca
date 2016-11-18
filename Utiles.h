#ifndef __UTILES_H__
#define __UTILES_H__
#include "definiciones.h"
#include <string>
using namespace std;


    int fecha_a_meses(int year, int mes);
    void meses_a_fecha(int &year, int &mes, int meses);
    string meses_a_string(int meses);
    void backline(void);
    string entero_a_texto (int n);
    string entero_a_texto (unsigned int n);
    BASE_TYPE texto_a_TipoBase(const string& s);
    string TipoBase_a_texto(BASE_TYPE &x);
    int texto_a_entero(const string& s);
    void colea();
    bool sigue_vivo();
    void progreso(BASE_TYPE porcentaje);
    string ConvierteUINTaHexString(unsigned int valor);
    unsigned int ConvierteHexStringaUINT(string cadena);
    string porcentaje(BASE_TYPE origen, BASE_TYPE actual, BASE_TYPE destino);
    bool TRAZA(string texto);
    bool TRAZA(string nombre, string texto);
	BASE_TYPE Lineal_Logaritmico(BASE_TYPE valor, BASE_TYPE minimo, BASE_TYPE maximo);
#endif

