// Math.cpp: implementation of the CMath class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMath::CMath()
{   
       POISSON_DISTRIBUTION = NULL;
       POISSON_SIZE = 0;
}

CMath::~CMath()
{
      delete []POISSON_DISTRIBUTION;
}

BASE_TYPE CMath::campo_medio(BASE_TYPE probabilidad, int poblacion)
{
  if (probabilidad < 0)
     probabilidad = -probabilidad;
  return (1.0-potencia(1.0-probabilidad, poblacion));
}
