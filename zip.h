#ifndef __ZIP_H__
#define __ZIP_H__

#include <cstdlib>
#include <iostream>
#include <stdio.h>

#ifdef __WIN32__
#include "dirent.h"
#endif

#ifdef __UNIX__
#include <dirent.h>
#endif

#include <time.h>
#include <string>
#include <vector>

#include "./zip/unzip.h"
#include "./zip/zip.h"

using namespace std;

class CZIP
{
    public:

    CZIP(string nombrearchivo = "");
    ~CZIP();

    void comprime(string archivo);
    void descomprime(string archivo);

    private:
    string m_nombre;
    string m_extension;
};

#endif
