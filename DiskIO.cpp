
// Archivos.cpp: define el punto de entrada de la aplicación de consola.
//

#include "DiskIO.h"
#include "Utiles.h"
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
#include <fstream>

using namespace std;


    CArchivoTexto::CArchivoTexto()
	{
		 pArchivo = NULL;
	 }

    CArchivoTexto::~CArchivoTexto()
	{
	   if (pArchivo)
		   fclose(pArchivo);
	}
// abre el archivo para lectura
    bool CArchivoTexto::AbreArchivoLectura(string archivo)
	{
       pArchivo = fopen(archivo.c_str(),"rt");
	   m_nombrearchivo = archivo;
	   if (pArchivo == NULL)
		   return false;
	   else
		   return true;
	}

	//abre el archivo para escritura desde cerp
	bool CArchivoTexto::AbreArchivoEscritura(string archivo)
	{
       pArchivo = fopen(archivo.c_str(),"wt");
	   m_nombrearchivo = archivo;
	   if (pArchivo == NULL)
		   return false;
	   else
		   return true;
	}

	//abre el archivo para escritura en modo append
    bool CArchivoTexto::AbreArchivoSeguirEscritura(string archivo)
	{
       pArchivo = fopen(archivo.c_str(),"at");
	   m_nombrearchivo = archivo;
	   if (pArchivo == NULL)
		   return false;
	   else
		   return true;
	}

	//guarda un dato en int pasándolo a texto antes
	bool CArchivoTexto::GuardaTexto(int datos)
	{
		return GuardaTexto(entero_a_texto(datos));
	}

	//guarda un dato en unsigned int pasándolo a texto antes
	bool CArchivoTexto::GuardaTexto(unsigned int datos)
	{
		return GuardaTexto(entero_a_texto(datos));
	}

	//guarda un dato en BASE_TYPE pasándolo a texto antes
	bool CArchivoTexto::GuardaTexto(BASE_TYPE datos)
	{
		return GuardaTexto(TipoBase_a_texto(datos));
	}

	//guarda una cadena
	bool CArchivoTexto::GuardaTexto(string datos)
	{
       if ( fwrite(datos.c_str(),1,datos.length() ,pArchivo) != datos.length())
		   return false;
	   else
		   return true;
	}

	// guarda un caracter
	bool CArchivoTexto::GuardaChar(char letra)
	{
		string t = " ";
		t[0] = letra;
		return GuardaTexto(t);
	}

	// Lee una cantidad de caracteres determinado de un archivo
	bool CArchivoTexto::LeeTexto(string &buffer, unsigned int cantidad)
	{
	   unsigned char valor;
	   unsigned int contador = cantidad;

	   buffer = "";
       if (pArchivo)
	   {
           while (contador)
		   {
		     if (fread(&valor,1,1,pArchivo) != 1)
				 return false;

             buffer.push_back (valor);
			 --contador;
		   }
		   return true;
	   }
	   else
		   return false;

	}

	// Lee una linea de texto hasta el siguiente LF
	// si el archivo no está abierto devuelve FALSE
    // y TRUE en cualquier otro caso. Si no se ha
    // podido leer nada, devuelve cadena vacía
	bool CArchivoTexto::LeeLinea(string &buffer)
	{
	   unsigned char valor;

	   buffer = "";
       if (pArchivo)
	   {
           while (fread(&valor,1,1,pArchivo) == 1)
		   {
		     if (valor != 10 && valor !=13)
                buffer.push_back (valor);
			 if (valor == 10) // LF
			   return true;
		   }
		   return true;
	   }
	   else
		   return false;

	}

	// como la anterior pero convirtiendo (si se puede) la linea a un entero sin signo
	bool CArchivoTexto::LeeLinea(unsigned int &entero)
	{
		string texto;
		bool abierto = LeeLinea(texto);
		entero = texto_a_entero(texto);
		return abierto;
	}

	// como la anterior pero convirtiendo (si se puede) la linea a un BASE_TYPE
	bool CArchivoTexto::LeeLinea(BASE_TYPE &entero)
	{
		string texto;
		bool abierto = LeeLinea(texto);
		entero = texto_a_TipoBase(texto);
		return abierto;

	}

	bool CArchivoTexto::LeePalabra(string &buffer)
	{
        // Lee una palabra (cualquier cosa delimitada por espacio, tabulador, LF o CR).
        // Si no se ha podido leer una palabra (por error o porque la línea está vacía)
        // devuelve false, o true en cualquier otro caso
	   unsigned char valor;
	   bool comienzo = false;
	   bool contenido = false;

	   buffer = "";
       if (pArchivo)
	   {
           while (fread(&valor,1,1,pArchivo) == 1)
		   {
             if ((valor == ' ' || valor == 10 || valor == 13 || valor == 9) && comienzo == true)
			       return contenido;

			 if ((valor != ' ' && valor != 10 && valor != 13 && valor != 9) && comienzo == false)
			    comienzo = true;

			 if (comienzo == true)
			 {
                buffer.push_back (valor);
				contenido = true;
			 }
		   }
		   return contenido;
	   }
	   else
		   return false;

	}
// lee la totalidad del archivo
	bool CArchivoTexto::LeeArchivoCompleto(string &buffer)
	{
	   unsigned char valor;

	   buffer = "";
       if (pArchivo)
	   {
           while (fread(&valor,1,1,pArchivo) == 1)
		   {
             buffer.push_back (valor);


		   }
		   return true;
	   }
	   else
		   return false;
	}
// cierra el archivo
	bool CArchivoTexto::CierraArchivo()
	{
       if (pArchivo != NULL)
	   {
         if (fclose (pArchivo))
		     return false;
	     else
	     {
		   pArchivo = NULL;
		   return true;
	     }
	   }
	   else
		   return true;
	}

	// borra el archivo
	bool CArchivoTexto::BorraArchivo()
	{
		CierraArchivo();
		if (remove(m_nombrearchivo.c_str ()) != 0)
			return false;
		else
			return true;
	}
//devuelve se ha llegado al final del archivo
    bool CArchivoTexto::FinDeArchivo()
	{

		if (!feof(pArchivo))
			return false;
		else
			return true;
	}

/************************************************************************/

// Similar a la clase anterior pero lee los datos en binario en vez de en modo texto
	CArchivoBinario::CArchivoBinario()
	{
		 pArchivo = NULL;
	 }

	CArchivoBinario::~CArchivoBinario()
	{
	   if (pArchivo)
		   fclose(pArchivo);
	}

	bool CArchivoBinario::AbreArchivoLectura(string archivo)
	{
       pArchivo = fopen(archivo.c_str(),"rb");
       m_nombrearchivo = archivo;

	   if (pArchivo == NULL)
		   return false;
	   else
		   return true;
	}

	bool CArchivoBinario::AbreArchivoEscritura(string archivo)
	{
       pArchivo = fopen(archivo.c_str(),"wb");
       m_nombrearchivo = archivo;
	   if (pArchivo == NULL)
		   return false;
	   else
		   return true;
	}

	bool CArchivoBinario::AbreArchivoLecturaEscritura(string archivo)
	{
       pArchivo = fopen(archivo.c_str(),"r+");
       m_nombrearchivo = archivo;
	   if (pArchivo == NULL)
		   return false;
	   else
		   return true;
	}

	bool CArchivoBinario::GuardaDatos(string datos)
	{
       if ( fwrite(datos.c_str(),1,datos.length() ,pArchivo) != datos.length())
		   return false;
	   else
		   return true;
	}

	bool CArchivoBinario::GuardaDatos(unsigned char* datos, unsigned int longitud)
	{
       if ( fwrite(datos,1,longitud ,pArchivo) != longitud)
		   return false;
	   else
		   return true;
	}

	bool CArchivoBinario::GuardaDatos(unsigned char* datos, unsigned int longitud, unsigned int posicion)
	{
       if (fseek ( pArchivo, posicion, SEEK_SET ) != 0)
         return false;
       if ( fwrite(datos,1,longitud ,pArchivo) != longitud)
		   return false;
	   else
		   return true;
	}

	bool CArchivoBinario::LeeDatos(string &buffer, unsigned int cantidad)
	{
	   unsigned char valor;
	   unsigned int contador = cantidad;

	   buffer = "";
       if (pArchivo)
	   {
           while (contador)
		   {
		     if (fread(&valor,1,1,pArchivo) != 1)
				 return false;

             buffer.push_back (valor);
			 --contador;
		   }
		   return true;
	   }
	   else
		   return false;

	}

	bool CArchivoBinario::LeeDatos(unsigned char *buffer, unsigned int cantidad)
	{

       if (pArchivo)
	   {
           if (fread(buffer,cantidad,1,pArchivo) != 1)
				 return false;
           else
		        return true;
	   }
	   else
		   return false;

	}

	bool CArchivoBinario::LeeDatos(unsigned char *buffer, unsigned int cantidad, unsigned int posicion)
	{

       if (pArchivo)
	   {
           if (fseek ( pArchivo, posicion, SEEK_SET ) != 0)
                 return false;

           if (fread(buffer,cantidad,1,pArchivo) != 1)
				 return false;
           else
		        return true;
	   }
	   else
		   return false;

	}

	bool CArchivoBinario::LeeArchivoCompleto(string &buffer)
	{
	   unsigned char valor;

	   buffer = "";
       if (pArchivo)
	   {
           while (fread(&valor,1,1,pArchivo) == 1)
		   {
             buffer.push_back (valor);
		   }
		   return true;
	   }
	   else
		   return false;
	}

    bool CArchivoBinario::CierraArchivoYMarcaEjecutable()
    {
        bool resultado = CierraArchivo();
#ifdef __UNIX__
        if (resultado)
           if (chmod(m_nombrearchivo.c_str(),S_IRWXU))
             return false;
#endif
        return resultado;

    }

	bool CArchivoBinario::CierraArchivo()
	{
       if (pArchivo !=NULL)
	   {
         if (fclose (pArchivo))
		     return false;
	     else
	     {
		   pArchivo = NULL;
		   return true;
	     }
	   }
	   else
		   return true;
	}

  bool CArchivoBinario::FinDeArchivo()
	{

		if (!feof(pArchivo))
			return false;
		else
			return true;
	}

  	bool CArchivoBinario::BorraArchivo()
	{
		CierraArchivo();
		if (remove(m_nombrearchivo.c_str ()) != 0)
			return false;
		else
			return true;
	}


/******************************************************************************************************/
/*
   Esta clase permite manejar los archivos de un directorio. Include funciones para leer el contenido
   de un directorio, buscar por extensión, nombre, etc.
*/
/******************************************************************************************************/
   CDirectorio::CDirectorio()
   {
      entradas = 0;
	  ruta_de_acceso = "";
   }

   CDirectorio::~CDirectorio()
   {
   }

   bool CDirectorio::LeeDirectorio(string ruta = "./")
   {
       // Lee el contenido de un directorio, si no se le indica ninguno lee el directorio donde estemos ejecutando

	   ruta_de_acceso = ruta;
       DIR *dp;
       struct dirent *ep;
	   entradas = 0;
	   directorio.clear();
	   tipo_entrada.clear();

       dp = opendir (ruta.c_str ());
       if (dp != NULL)
         {
           while ((ep = readdir (dp)))
		   {
             directorio.push_back (ep->d_name);
#ifdef __UNIX__
             if (ep->d_type == DT_DIR)
#endif
#ifdef __WIN32__
             if (ep->data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
#endif

				 tipo_entrada.push_back(ES_DIRECTORIO);
			 else
				 tipo_entrada.push_back(ES_ARCHIVO);
			 ++entradas;
		   }
           (void) closedir (dp);
		   return true;
         }
       else
         return false;
   }

   string CDirectorio::Entrada(unsigned int entrada)
   {
       // Devuelve el nombre completo (incluye la ruta) de un nº de entrada al directorio determinado.
       // El nombre retornado es utilizable directamente por CArchivoTexto o CArchivoBinario
      if (entrada < entradas)
		  return ruta_de_acceso+directorio[entrada];
	  else
		  return "";
   }

  string CDirectorio::Nombre(unsigned int entrada)
   {
       // Devuelve el nombre (sin la ruta ni la extensión) de un nº de entrada determinado.

      if (entrada < entradas)
	  {
		  unsigned int final = (unsigned int) directorio[entrada].find_last_of('.');
		  if (final != directorio[entrada].npos)
			    return (directorio[entrada].substr(0,final));
			      return directorio[entrada];
	  }
	  else
		  return "";
   }

 string CDirectorio::NombreCompleto(unsigned int entrada)
   {
       // Devuelve el nombre y extension de un nº de entrada determinado.

      if (entrada < entradas)
	  {
	      return directorio[entrada];
	  }
	  else
		  return "";
   }

  string CDirectorio::RutaNombre(unsigned int entrada)
   {
       // Devuelve el nombre completo (incluye la ruta pero NO la extensión) de un nº de entrada determinado.

      string nombre;
	  nombre = Nombre(entrada);

	  if (nombre != "")
		  return (ruta_de_acceso+nombre);
	  else
		  return "";
   }

   string CDirectorio::Extension(unsigned int entrada)
   {
       // Devuelve la extensión de un nº de entrada determinado.

      if (entrada < entradas)
	  {
		  unsigned int final = (unsigned int) directorio[entrada].find_first_of('.');
		  if (final != directorio[entrada].npos)
			  return (directorio[entrada].substr(final+1));
	  }

	  return "";

   }

   void CDirectorio::dump()
   {
       // volcado por pantalla del contenido del directorio
     for (unsigned int cnt = 0; cnt < entradas; cnt++)
		 cout << directorio[cnt] << endl ;
   }

   unsigned int CDirectorio::Entradas()
   {
       // devuelve el número de entradas que tiene el directorio
     return entradas;
   }

   int CDirectorio::ExisteEntrada(string nombrearchivo)
   {
       // indica si un determinado archivo (incluyendo nombre y extensión) están en el directorio
       // y si está devuelve su posición, -1 en caso contrario
     for ( unsigned int cnt = 0; cnt < entradas; cnt++)
     {
  		 if (directorio[cnt] == nombrearchivo)
			 return cnt;
     }

	 return -1;
   }

   string CDirectorio::BuscaPrimeroConExtension(string extension)
   {
       // Busca el primer archivo que haya en el directorio con una extensión determinada
       // y si lo encuentra develve su nombre completo
      for (unsigned int cnt = 0; cnt < entradas; cnt++)
	  {
		  unsigned int final = (unsigned int) directorio[cnt].find_first_of('.');
		  if (final != directorio[cnt].npos)
		  {
             if (directorio[cnt].substr(final+1) == extension)
				 return directorio[cnt];
		  }
	  }

	  return "";

   }

   string CDirectorio::BuscaRutaPrimeroConExtension(string extension)
   {
       // busca el primer archivo que haya con una extensión determinada y si lo encuentra
       // devuelve el nombre completo con la ruta de acceso, utilizable directamente por CArchivoxxx
	   string cadena;
	   cadena = BuscaPrimeroConExtension(extension);

		if ( cadena != "")
		   return ruta_de_acceso+cadena;
		else
		   return "";
   }

   void CDirectorio::Actualiza()
   {
       // Actualiza el contenido del directorio, debería llamarse a esta función con cada cambio (borrado, creación, renombrado)
       // que haya ocurrido
       LeeDirectorio(ruta_de_acceso);
   }

      time_t CDirectorio::Antiguedad(unsigned int entrada)
   {
       // devuelve la antiguedad de la fecha de modificación de un archivo dado según su entrada
       // en el directorio
      int result;
	  struct stat tiempoarchivo;
	  struct timeb tiempoactual;

      if (entrada < entradas)
      {
	    string archivo =  ruta_de_acceso+directorio[entrada];
		result = stat( archivo.c_str (), &tiempoarchivo );
		if (result)
			return 0;

		ftime(&tiempoactual);
		time_t timediff = tiempoactual.time - tiempoarchivo.st_mtime;

		return timediff;
	  }

       return 0;
   }

   bool CDirectorio::ActualizaHora(string nombrearchivo)
   {
       // permite cambiar la fecha de un archivo a la del sistema en ese momento
      int pos = ExisteEntrada(nombrearchivo);
      if ( pos>= 0)
	  {
		  ActualizaHora((unsigned int) pos);
		  return true;
	  }

	  return false;
   }

   bool CDirectorio::ActualizaHora(unsigned int entrada)
   {
       // idem para una entrada
	  int result = 0;
      if (entrada < entradas)
      {
	    string archivo =  ruta_de_acceso+directorio[entrada];
		result = utime(archivo.c_str (), NULL);
		if (result == 0)
		   return true;
		else
		   return false;
	  }
	  return false;
   }


   bool CDirectorio::Renombra(string nuevonombre,unsigned int entrada)
   {
       // permite renombrar una entrada del directorio con otro nombre
	  string aux = "";
	  int result = 0;
      if (entrada < entradas)
      {
	    string archivo =  ruta_de_acceso+directorio[entrada];
		aux = ruta_de_acceso + nuevonombre;
		result = rename(archivo.c_str () ,aux.c_str() );
		if (result == 0)
		{
           Actualiza();
		   return true;
		}
		else
		   return false;
	  }
	  return false;
   }

   bool CDirectorio::CambiaExtension(string nuevaextension, string nombrearchivo)
   {
       // permite cambiar la extensión de un archivo determinado
     for (unsigned int cnt = 0; cnt < entradas; cnt++)
		 if (directorio[cnt] == nombrearchivo)
		 {
			 return CambiaExtension(nuevaextension,cnt);
		 }
	 return false;
   }

   bool CDirectorio::CambiaExtension(string nuevaextension,unsigned int entrada)
   {
       // permite cambiar la extensión de una entrada determinada
	  string aux = "";
	  string archivo = "";
	  int result = 0;

      if (entrada < entradas)
      {
	    string aux =  RutaNombre(entrada)+"."+nuevaextension;
		archivo = ruta_de_acceso+directorio[entrada];

		result = rename(archivo.c_str () ,aux.c_str() );
		if (result == 0)
		{
           Actualiza();
		   return true;
		}
		else
		   return false;
	  }
	  return false;
   }


   bool CDirectorio::Renombra(string nuevonombre,string viejonombre)
   {
       // permite renombrar un archivo
       if (rename(viejonombre.c_str (), nuevonombre.c_str ()))
		   return false;
	   else
	   {
          Actualiza();
		  return true;
	   }


   }

   unsigned int CDirectorio::CuentaArchivos(string extension)
   {
       // cuenta cuantos archivos con una extensión determinada hay
     unsigned int cuantos = 0;
	 string ext = "";
     for (unsigned int cnt = 0; cnt < entradas; cnt++)
	 {
		 ext = Extension(cnt);
		 if ( ext == extension)
		    ++cuantos;
	 }
	 return cuantos;

   }

   bool CDirectorio::BorraArchivo(unsigned int entrada)
   {
       // borra el archivo de una entrada determinada
	  int result;

      if (entrada < entradas)
      {
	    string archivo =  ruta_de_acceso+directorio[entrada];
		result = remove(archivo.c_str());
		if (result == 0)
		{
           Actualiza();
		   return true;
		}
		else
		   return false;
	  }
	  return false;
   }

   bool CDirectorio::MueveArchivo(unsigned int entrada, string destino)
   {
       // mueve el archivo de una entrada determinada a otro directorio
      if (entrada < entradas)
      {
	    string archivoorigen =  ruta_de_acceso + directorio[entrada];
		string archivodestino = destino + directorio[entrada];

         if (rename(archivoorigen.c_str(), archivodestino.c_str()))
		   return false;
	   else
	   {
          Actualiza();
		  return true;
	   }
	  }
	  return false;
   }

bool CDirectorio::CopiaArchivo(unsigned int entrada, string destino)
   {
       // copia el archivo de una entrada determinada a otro directorio
      if (entrada < entradas)
      {
	    string archivoorigen =  ruta_de_acceso + "/" + directorio[entrada];
		string archivodestino = destino + directorio[entrada];
		CopiaArchivo(archivoorigen,archivodestino);
		return true;
	  }
	  return false;
   }

bool CDirectorio::CopiaArchivo(string origen, string destino)
   {
       // copia el archivo 
		ifstream f1(origen.c_str(), fstream::binary);
		ofstream f2(destino.c_str(), fstream::trunc|fstream::binary);
		f2 << f1.rdbuf();
        Actualiza();
		return true;
   }

   unsigned int CDirectorio::MueveArchivosPorExtension(string extension, string destino)
   {
       // mueve todos los archivos con una extensión determinada a otro directorio
	 unsigned int cuantos = 0;
	 string ext = "";
     for (unsigned int cnt = 0; cnt < entradas; cnt++)
	 {
		 ext = Extension(cnt);
		 if ( ext == extension)
		 {
           string archivoorigen =  ruta_de_acceso + directorio[cnt];
		   string archivodestino = destino + directorio[cnt];
           if (!rename(archivoorigen.c_str(), archivodestino.c_str()))
		      ++cuantos;
		 }
	 }
	 Actualiza();
	 return cuantos;
   }

   unsigned int CDirectorio::BorraArchivoPorNombre(string nombre, string extension)
   {
       // borra los archivos con un nombre o extensión determinados.
       // si el nombre y la extensión están vacios o son * los borra todos
	 unsigned int cuantos = 0;
	 string ext = "";
     string nom = "";
     for (unsigned int cnt = 0; cnt < entradas; cnt++)
	 {
		 ext = Extension(cnt);
         nom = Nombre(cnt);


		 if ( (ext == extension || extension == "" || extension == "*") &&
              (nom == nombre    || nombre =="" || nombre == "*"))
		 {
           string archivo =  ruta_de_acceso + directorio[cnt];
           if (!remove(archivo.c_str()))
		      ++cuantos;
		 }
	 }
	 Actualiza();
	 return cuantos;
   }

   bool CDirectorio::EsDirectorio(unsigned int entrada)
   {
	   return (tipo_entrada[entrada] == ES_DIRECTORIO);

   }

   CDirectorio CDirectorio::EntraEnDirectorio(unsigned int entrada)
   {
		string nuevodestino = Entrada(entrada);
		CDirectorio dir;
		if (nuevodestino!="" && tipo_entrada[entrada] == ES_DIRECTORIO)
		{
			dir.LeeDirectorio(nuevodestino);
		}

		return dir;
   }

   string CDirectorio::NombreDirectorio()
   {
	   return ruta_de_acceso;
   }
/******************************************************************************************************/
/*
   Esta clase calcula el CRC (Checksum) de 8 bits de una cadena.
*/
/******************************************************************************************************/

   CCRC::CCRC()
   {
	  CRC = 0;
   }
   CCRC::~CCRC()
   {

   }

   unsigned int CCRC::CalculaCRC(string cadena)
   {
       //devuelve el CRC de 8 bits de una cadena
	   unsigned int pos = 0;
	   CRC = 0;
	   for (pos = 0; pos < cadena.length(); pos++)
	   {
          CRC += (unsigned char) cadena[pos];
	   }
	   return CRC;
   }

   bool CCRC::CompruebaCRC(string cadena)
   {
       //comprueba si una cadena tiene el CRC correcto. Dicho CRC debe ser el último caracter
       // de la cadena
	   unsigned int pos = 0;
	   CRC = 0;
	   if (cadena == "")
		   return false;

	   for (pos = 0; pos < cadena.length() - 1; pos++)
	   {
          CRC += cadena[pos];
	   }
	   if (CRC == (unsigned char) cadena[cadena.length()-1])
		   return true;
	   else
		   return false;
   }

   string CCRC::InsertaCRC(string &cadena)
   {
       // calcula el CRC de una cadena e inserta dich valor al final
		unsigned char crc = CalculaCRC(cadena);
		cadena += crc;
		return cadena;
   }

   unsigned int CCRC::LargoCRC()
   {
      return 1;
   }

/******************************************************************************************************/
/*
   Esta clase calcula el CRC (Checksum) de 32 bits de una cadena.
*/
/******************************************************************************************************/

   CCRC32::CCRC32()
   {
	  CRC = 0;
      CRCASCII = "00000000";
   }
   CCRC32::~CCRC32()
   {

   }

   unsigned int CCRC32::CalculaCRC(string cadena)
   {
       //devuelve el CRC de 32 bits de una cadena
	   unsigned int pos = 0;
	   CRC = 0;
	   for (pos = 0; pos < cadena.length(); pos++)
	   {
          CRC += (unsigned int) cadena[pos];
	   }
	   return CRC;
   }

   string CCRC32::CalculaCRCASCII(string cadena)
   {
       CalculaCRC(cadena);
       CRCASCII = ConvierteUINTaHexString(CRC);
	   return CRCASCII;
   }

   bool CCRC32::CompruebaCRC(string cadena)
   {
       //comprueba si una cadena tiene el CRC correcto. Dicho CRC deben ser los 4 últimos caracteres
       // de la cadena
	   unsigned int pos = 0;
       unsigned int calculado = 0;
       unsigned int byte1,byte2,byte3,byte4;
	   CRC = 0;
	   if (cadena == "" || cadena.length() <= LargoCRC())
		   return false;

	   for (pos = 0; pos < cadena.length() - LargoCRC(); pos++)
	   {
          CRC += (unsigned int) cadena[pos];
	   }

        byte4 = (unsigned char) cadena[pos++];
        byte3 = (unsigned char) cadena[pos++];
        byte2 = (unsigned char) cadena[pos++];
        byte1 = (unsigned char) cadena[pos++];

        calculado = byte4*0x1000000 + byte3*0x10000 + byte2*0x100 + byte1;

	   if (CRC == calculado)
		   return true;
	   else
		   return false;
   }

   bool CCRC32::CompruebaCRCASCII(string cadena)
   {
       //comprueba si una cadena tiene el CRC correcto. Dicho CRC deben ser los 8 últimos caracteres
       // de la cadena
	   unsigned int pos = 0;
       unsigned int calculado = 0;
       string   crc;
	   CRC = 0;
	   if (cadena == "" || cadena.length() <= LargoCRCASCII())
		   return false;

	   for (pos = 0; pos < cadena.length() - LargoCRCASCII(); pos++)
	   {
          CRC += (unsigned int) cadena[pos];
	   }
       
       calculado = ConvierteHexStringaUINT(cadena.substr(pos,8));

	   if (CRC == calculado)
		   return true;
	   else
		   return false;
   }

   string CCRC32::InsertaCRC(string &cadena)
   {
       // calcula el CRC de una cadena e inserta dich valor al final
		unsigned int crc = CalculaCRC(cadena);
        unsigned char byte1,byte2,byte3,byte4 = 0;

        byte1 = crc             & 0x000000FF;
        byte2 = (crc/0x100)     & 0x000000FF;
        byte3 = (crc/0x10000)   & 0x000000FF;
        byte4 = (crc/0x1000000) & 0x000000FF;
		cadena += byte4;
        cadena += byte3;
        cadena += byte2;
        cadena += byte1;
		return cadena;
   }

   string CCRC32::InsertaCRCASCII(string &cadena)
   {
       // calcula el CRC de una cadena e inserta dich valor al final
		string crc = CalculaCRCASCII(cadena);
        cadena += crc;
		return cadena;
   }

  unsigned int CCRC32::LargoCRC()
   {
      return 4;
   }

  unsigned int CCRC32::LargoCRCASCII()
   {
      return 8;
   }

  