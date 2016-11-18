#include "aleatorio.h"
#include "mprandom.h"

CRandomPMBD::CRandomPMBD()
	{
		idum = (int)-time(NULL);
        Rnd();
	}

CRandomPMBD::~CRandomPMBD(){}

	float CRandomPMBD::operator()()
	{
        return Rnd();
	}

	int CRandomPMBD::IntRnd(int min, int max)
	{
       int rango = (max - min + 1);

	   float valor = Rnd();

	   /*if (valor == 1.0 || valor == 0.0)
		   cout << "LIMITE";
       */

	   return (int) (valor * (float)rango + min);

	}

	float CRandomPMBD::Rnd()
	{
	  int j;
	  long k;
	  static long iy=0;
	  static long iv[NTAB];
	  float temp;

	  if (idum <= 0 || !iy)
	  {// Initialize.
		 if (-(idum) < 1)
			 idum=1; // Be sure to prevent idum = 0.
		 else
			 idum = -(idum);

		 for (j = NTAB + 7 ; j >= 0 ; j--)
		 {// Load the shuffle table (after 8 warm-ups).
			 k = (idum)/IQ;
			 idum = IA*(idum-k*IQ)-IR*k;
			 if (idum < 0)
				 idum += IM;
			 if (j < NTAB)
				 iv[j] = idum;
		 }
		 iy = iv[0];
	  }

	  k = (idum)/IQ;// Start here when not initializing.
	  idum = IA*(idum-k*IQ)-IR*k; //Compute idum=(IA*idum) % IM without overflows by Schrage's method.
	  if (idum < 0)
		  idum += IM;
	  j = iy/NDIV; //Will be in the range 0..NTAB-1.
	  iy = iv[j]; //Output previously stored value and reill the
	  iv[j] = idum; //shuffle table.
	  if ((temp = (float)AM*iy) > RNMX)
		  return (float)RNMX; // Because users don't expect endpoint values.
	  else
		  return temp;
	}


// Esta clase genera numeros aleatorios usando rand() de la biblioteca estandar


    CDado::CDado()
    {

    }

    void CDado::Inicia(void)
    {
        srand( (unsigned)time(NULL) );
    }

	BASE_TYPE CDado::Tira()
    {
      return (BASE_TYPE)rand()/(BASE_TYPE)RAND_MAX;
    }

    // Devuelte un entero entre 1..max
    unsigned int CDado::TiraMaxInt(unsigned int max)
    {
      return ((unsigned int)(rand()%max)+1);
    }


// Esta clase genera numeros aleatorios usando
// L'Ecuyer's 1996 Tausworthe generator taus88

    CDadoTAUS88::CDadoTAUS88(unsigned long inicializador)
    {
	   dado = new MATPACK::Ran088(inicializador);
    }

    CDadoTAUS88::CDadoTAUS88()
    {
	   dado = new MATPACK::Ran088();
    }

    CDadoTAUS88::~CDadoTAUS88()
    {
	   delete dado;
    }

    void CDadoTAUS88::Inicia(void)
    {

    }

    void CDadoTAUS88::Inicia(unsigned long inicializador)
    {
          delete dado;
          dado = new MATPACK::Ran088(inicializador);
    }

    // Devuelte un float entre 0..1
	BASE_TYPE CDadoTAUS88::TiraFloat()
    {
       return (BASE_TYPE)((BASE_TYPE)dado->Long()/((BASE_TYPE)4294967295U));
    }

    // Devuelte un entero entre 0..4294967295U
    unsigned int CDadoTAUS88::TiraInt()
    {
       return dado->Long();
    }

    // Devuelte un entero entre min..max
    unsigned int CDadoTAUS88::TiraRangoInt(unsigned int min, unsigned int max)
    {
       //unsigned int rango = (max - min + 1);
	   //unsigned int valor = dado->Long();
	   return (unsigned int) (min + dado->Long()%(max - min + 1));
    }

