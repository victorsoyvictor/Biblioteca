// Math.h: interface for the CMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATH_H__0E427F31_9D67_4817_8D71_0B3B804F7B72__INCLUDED_)
#define AFX_MATH_H__0E427F31_9D67_4817_8D71_0B3B804F7B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <stdlib.h>
#include <iostream>
//#include <conio.h>
#include <time.h>

#include "definiciones.h"

using namespace std;

class CMath  
{

public:
	BASE_TYPE campo_medio ( BASE_TYPE probabilidad, int poblacion);

    BASE_TYPE *POISSON_DISTRIBUTION;
    BASE_TYPE POISSON_SIZE;

	CMath();

	virtual ~CMath();


    void inicia_dado()
    {
	   srand( (unsigned)time(NULL) );
    }

	BASE_TYPE dado()
    {
      return (BASE_TYPE)rand()/(BASE_TYPE)RAND_MAX;
    }

    BASE_TYPE factorial(BASE_TYPE numero)
    {
        BASE_TYPE acumulador = 1;

    	while (numero>0)
	    {
	        acumulador *= numero;
		    --numero;
	    }

        return acumulador;
    }

    BASE_TYPE potencia(BASE_TYPE base, int exponente)
    {
	    return pow( base, exponente);
    }

    BASE_TYPE POISSON ( BASE_TYPE NUMERO_DE_OCURRENCIAS_K, 
                        BASE_TYPE MEDIA_LAMBDA)
    {

        BASE_TYPE e_exp = exp(-MEDIA_LAMBDA);
        BASE_TYPE pot   = potencia(MEDIA_LAMBDA,(int)NUMERO_DE_OCURRENCIAS_K);
        BASE_TYPE fact  = factorial(NUMERO_DE_OCURRENCIAS_K);
        BASE_TYPE total = e_exp * pot / fact;

        return (total);
    }

    BASE_TYPE distribucion_POISSON (BASE_TYPE ratio)
    {
   
        BASE_TYPE suma = 0.0;
        BASE_TYPE i = 0;
        BASE_TYPE MAX_I = 128;
        BASE_TYPE *AUX_VECTOR = NULL;

        delete [] POISSON_DISTRIBUTION;

        POISSON_DISTRIBUTION = new BASE_TYPE[(int)MAX_I+1];
        
        while ( suma < 0.999999)
        {
          suma = 0;

          for (int k = 0; k <= i ; k++)
	      {
            suma += POISSON(k,ratio);
	      }

	      POISSON_DISTRIBUTION[(int)i] = suma;

          i++;
//          cout << i << " terminos de Poisson suman " << suma << " convergiendo a 1"; 
//		    cout << (char) 13;

          if (i >= MAX_I)
          { 
            AUX_VECTOR = new BASE_TYPE[(int)i+10];
            for (int pos = 0; pos < i ; pos++)
              AUX_VECTOR[pos] = POISSON_DISTRIBUTION[pos];

            delete [] POISSON_DISTRIBUTION;
            POISSON_DISTRIBUTION = AUX_VECTOR;
            AUX_VECTOR = NULL;
            MAX_I += 10;
          
          }
        }

        POISSON_SIZE = i;
        return i;

    }

    BASE_TYPE POISSON_mayor_que(BASE_TYPE probabilidad)
    {
       for (int i = 0; i < POISSON_SIZE; i++)
         if ( POISSON_DISTRIBUTION[i] > probabilidad)
           return i;

       return POISSON_SIZE;
   
    }

	BASE_TYPE EXP(int exponente)
	{	   

       BASE_TYPE ACUM = NUMERO_E;

	   if (exponente == 0)
		 return ACUM;

	   if (exponente > 0)
	     for (int i = 1; i < exponente; i++)
		 {
            ACUM = ACUM*NUMERO_E;
		 }
	   else
	   {
	     for (int i = -1; i > exponente; i--)
		 {
            ACUM = ACUM*NUMERO_E;
		 }

		 ACUM = 1.0 / ACUM;
	   }

       return ACUM;
    
	}

};

#endif // !defined(AFX_MATH_H__0E427F31_9D67_4817_8D71_0B3B804F7B72__INCLUDED_)
