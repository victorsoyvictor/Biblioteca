#ifndef __CPOISSON_H__
#define __CPOISSON_H__
#include <cmath>
#include <vector>
#include <iostream>
#include "definiciones.h"
#include "Utiles.h"

class CPoisson
{

private:
	vector<BASE_TYPE> m_serie_Poisson;
	BASE_TYPE m_LAMBDA;
	BASE_TYPE m_max_K;

public:

	void Inicializa(BASE_TYPE LAMBDA)
	{
       m_LAMBDA = LAMBDA; //media de la serie
	   m_max_K  = 0;
	   distribucion (m_LAMBDA);
	}

	CPoisson()
	{
       m_LAMBDA = 0; //media de la serie
	   m_max_K  = 0;
       //m_serie_Poisson = NULL;
       m_serie_Poisson.resize(0);
	   distribucion (m_LAMBDA);
	}

	CPoisson(BASE_TYPE LAMBDA)
	{
       m_LAMBDA = LAMBDA; //media de la serie
	   m_max_K  = 0;
       //m_serie_Poisson = NULL;
       m_serie_Poisson.resize(0);
	   distribucion (m_LAMBDA);
	}

	virtual ~CPoisson()
	{
		//delete []m_serie_Poisson;
	};

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
	    return pow((BASE_TYPE)base, (BASE_TYPE)exponente);
    }

    BASE_TYPE TerminoPoisson ( BASE_TYPE NUMERO_DE_OCURRENCIAS_K,
                               BASE_TYPE MEDIA_LAMBDA)
    {

        BASE_TYPE e_exp = exp(-MEDIA_LAMBDA);
        BASE_TYPE pot   = potencia(MEDIA_LAMBDA,(int)NUMERO_DE_OCURRENCIAS_K);
        BASE_TYPE fact  = factorial(NUMERO_DE_OCURRENCIAS_K);
        BASE_TYPE total = e_exp * pot / fact;
        return (total);
    }

    BASE_TYPE distribucion (BASE_TYPE ratio)
    {

		// Hacemos dos pasadas
        BASE_TYPE suma = 0.0;
        BASE_TYPE sumaanterior = 1.0;
        BASE_TYPE i = 0;
        //BASE_TYPE MAX_I = 128;
        //BASE_TYPE *AUX_VECTOR = NULL;

        //delete [] m_serie_Poisson;
        //m_serie_Poisson = new BASE_TYPE[(int)MAX_I+1];

        do
        {
          sumaanterior = suma;
          suma = 0;

          for (int k = 0; k <= i ; k++)
	      {
            suma += TerminoPoisson(k,ratio);
	      }

          if (m_serie_Poisson.size() <= i)
            m_serie_Poisson.push_back(0);

	      m_serie_Poisson[(int)i] = suma;

          i++;
/*
          std::cout << i << " terminos de Poisson suman " << TipoBase_a_texto(suma) << " convergiendo a 1              ";
          cout << endl;
*/
          //backline();
          //std::cout << "Size " << sizeof(BASE_TYPE) << std::endl;

/*
          if (i >= MAX_I)
          {
            AUX_VECTOR = new BASE_TYPE[(int)i+10];
            for (int pos = 0; pos < i ; pos++)
              AUX_VECTOR[pos] = m_serie_Poisson[pos];

            delete [] m_serie_Poisson;
            m_serie_Poisson = AUX_VECTOR;
            AUX_VECTOR = NULL;
            MAX_I += 10;
          }
*/
        } while ( suma != sumaanterior );

        //como para cuando se repiten dos elementos, hay que borrar el último
        m_serie_Poisson.pop_back();
        i--;

        // Cerramos el último valor de la serie con probabilidad 1
        m_serie_Poisson[(unsigned int)i-1] = 1.0;
        m_max_K = i;
        //cout << endl;
        return i;
    }

    BASE_TYPE mayor_que(BASE_TYPE probabilidad)
    {
       for (int i = 0; i < m_max_K; i++)
         if ( m_serie_Poisson[i] > probabilidad)
           return i;

       return m_max_K;

    }

   BASE_TYPE termino(unsigned int pos)
    {
       if (pos < m_max_K)
          return m_serie_Poisson[(int)pos];
       else
          return m_serie_Poisson[(int)m_max_K-1];
    }

   unsigned int num_terminos()
   {
       return (unsigned int) m_max_K;
   }
};

#endif

