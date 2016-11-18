
// Archivos.cpp: define el punto de entrada de la aplicación de consola.
//

#include "zip.h"

#ifdef __UNIX__
#include <utime.h>
#endif

#ifdef __WIN32__
#include <sys/utime.h>
#endif

#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <time.h>

#include "./zip/unzip.h"
#include "./zip/zip.h"

using namespace std;

    CZIP::CZIP(string nombrearchivo)
    {
        /*
        m_nombre = "";
        m_extension = "";
        if (nombrearchivo.length() == 0)
          return;
        bool punto = false;
        int position = 0;

        for (int x = nombrearchivo.length() - 1; x >= 0; x--)
        {
            if (nombrearchivo[x] == '.' && !punto)
            {
               punto = true;
               posicion = x;
            }
        }

        if (!punto)
           m_nombre = nombrearchivo;
        else
        {
            m_nombre = nombrearchivo.substr(0,nombrearchivo.length()-posicion);
            m_extension = nombrearchivo.substr(nombrearchivo.length()-posicion+1,posicion);
        }
        */
    }

    CZIP::~CZIP(){}

    void CZIP::comprime(string archivo)
    {
        string destino = archivo+".zip";
        HZIP hz = CreateZip(destino.c_str(),0);
        ZipAdd(hz,archivo.c_str(), archivo.c_str());
        CloseZip(hz);

    }

    void CZIP::descomprime(string archivo)
    {
       HZIP hz = OpenZip(archivo.c_str(),0);
       ZIPENTRY ze; GetZipItem(hz,-1,&ze); int numitems=ze.index;
       for (int i=0; i<numitems; i++)
       { GetZipItem(hz,i,&ze);
         UnzipItem(hz,i,ze.name);
       }
       CloseZip(hz);
    }


