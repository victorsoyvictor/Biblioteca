#include "Hilos.h"

#include <cstdlib>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>

#ifdef __UNIX__
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "Reloj.h"
#endif

using namespace std;

CHilos::CHilos()
{
    std::string FullPathToExe = "";
    std::string Parameters = "";
	std::string WorkingDir = "";
#ifdef __WIN32__
	size_t SecondsToWait = 0;
	dwExitCode = 0;
#endif
#ifdef __UNIX__
    processID = 0;
#endif
}

CHilos::~CHilos()
{
#ifdef __WIN32__
  //Done here to prevent memory leaks
  CloseHandle(piProcessInfo.hProcess);
  CloseHandle(piProcessInfo.hThread);
#endif
}

bool CHilos::InicializaHilo(
				   std::string ruta,
				   std::string parametros,
				   std::string directorio,
				   size_t timeout)
{
	FullPathToExe = ruta;
    Parameters = parametros;
	WorkingDir = directorio;
	SecondsToWait = timeout;

#ifdef __WIN32__
	size_t iMyCounter = 0;
	size_t iReturnVal = 0;
#endif
	size_t iPos = 0;
    std::string sTempStr = "";

    /* Add a space to the beginning of the Parameters */
    if (Parameters.size() != 0)
    {
        if (Parameters[0] != ' ')
        {
            Parameters.insert(0," ");
        }
    }

    /* The first parameter needs to be the exe itself */
    sTempStr = FullPathToExe;
    iPos = sTempStr.find_last_of("\\");
    sTempStr.erase(0, iPos +1);
    Parameters = sTempStr.append(Parameters);

     /* CreateProcess can modify Parameters thus we allocate needed memory */

    const char* pchrTemp = Parameters.c_str();
    strcpy(Param, pchrTemp);
#ifdef __WIN32__
    /* CreateProcess API initialization */
    memset(&siStartupInfo, 0, sizeof(siStartupInfo));
    memset(&piProcessInfo, 0, sizeof(piProcessInfo));
    siStartupInfo.cb = sizeof(siStartupInfo);
#endif

    return true;
}

bool CHilos::LanzaHilo()
{

#ifdef __WIN32__
	int iReturnVal = 0;
    if (
        CreateProcessA(FullPathToExe.c_str(),
                       Param,
					   0,
					   0,
					   false,
                       CREATE_DEFAULT_ERROR_MODE,
					   0,
					   WorkingDir.c_str(),
                       &siStartupInfo,
					   &piProcessInfo) != false)
    {
        return true;
    }
    else
    {
        /* CreateProcess failed */
        iReturnVal = GetLastError();
		return false;
    }
#endif
#ifdef __UNIX__
  // No se usa la lista de parámetros
  if  (( processID = fork() ) == 0 )		// Create child
 {
         execlp(FullPathToExe.c_str(),
                FullPathToExe.c_str(),
                NULL);
         exit(-1);
}
  else if( processID == -1 )
{
           processID = 0;
           return false;
}
  else
    return true;

#endif

  return false;
}

bool CHilos::HiloCorriendo()
{
   /* Watch the process. */
#ifdef __UNIX__
    extern int errno;
    int result;
    int status = waitpid(processID, &result,WNOHANG);

     //cout << status << " " << result << " " << errno << endl << endl;
    if ( status == -1 )
    {
         return false;
    }
    else
    {
        return true;
    }

#endif
#ifdef __WIN32__
   dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, (1 * 1000));

   switch (dwExitCode)
   {
   case  WAIT_TIMEOUT:
	   return true;
	   break;

   default:
	   return false;
	   break;
   }
#endif
  return false;
}

void CHilos::MataHilo()
{
#ifdef __WIN32__
  cout << "Terminacion de emergencia" << TerminateProcess(piProcessInfo.hProcess,0) << endl;
  /* Release handles */

  CloseHandle(piProcessInfo.hProcess);
  CloseHandle(piProcessInfo.hThread);
#endif
#ifdef __UNIX__
  kill (processID,SIGKILL );
#endif
}

bool CHilos::EsperaTermino(int segundos)
{
#ifdef __WIN32__
   dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, (segundos * 1000));
   switch (dwExitCode)
   {
   case  WAIT_TIMEOUT:
	   return false;
	   break;

   default:
	   return true;
	   break;
   }
#endif
#ifdef __UNIX__
  CReloj reloj;
  bool salir = false;
  while (!salir)
  {
      reloj.espera(1);
      if (reloj.segundos_transcurridos() > segundos || !HiloCorriendo())
         salir = true;
  }

  return !HiloCorriendo();
#endif
  return false;

}
