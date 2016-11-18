#ifndef __RELOJ_H__
#define __RELOJ_H__

#include <time.h>
#include <ctime>
#include <string>
#define SEGUNDOS true
#define TICKS    false
using namespace std;

class CReloj
{
private:
    time_t tiempoInicial;
    time_t tiempoFinal;
    clock_t tickstart, tickfinish;
    bool segundos_o_ticks;

public:
	CReloj(bool segundos = SEGUNDOS);
	virtual ~CReloj();
    void reinicia_reloj();
	double segundos_transcurridos();
    string tiempo_transcurrido_largo();
	string tiempo_transcurrido_corto();
	double segundos_ahora();
	string tiempo_ahora();
    string estima_tiempo(unsigned int periodoinicial, unsigned int periodoactual, unsigned int periodofinal);
	double estima_segundos(unsigned int periodoinicial, unsigned int periodoactual, unsigned int periodofinal);
    string fecha_y_hora();
	void espera(int segundos);
	unsigned int tiempo_de_vuelo();
};

bool operator>(CReloj reloj, string fechahora);

#endif

