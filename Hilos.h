#ifndef __HILOS_H__
#define __HILOS_H__

#include <cstdlib>
#include <string>
#include <cstring>
#ifdef __WIN32__
#include <windows.h>
#endif

using namespace std;
#define MAX_PARAM 1024;

class CHilos
{
public:
	CHilos();
	~CHilos();
	bool InicializaHilo(string ruta,
				        string parametros,
				        string directorio,
				        size_t timeout);
	bool LanzaHilo();
	bool HiloCorriendo();
	void MataHilo();
	bool EsperaTermino(int segundos);

private:
	string FullPathToExe;
    string Parameters;
	string WorkingDir;
	size_t SecondsToWait;
#ifdef __WIN32__
	STARTUPINFOA siStartupInfo;
    PROCESS_INFORMATION piProcessInfo;
	DWORD dwExitCode;
#endif
#ifdef __UNIX__
    unsigned int dwExitCode;
    int processID;
#endif
	char Param[1024+1];


};

#endif
