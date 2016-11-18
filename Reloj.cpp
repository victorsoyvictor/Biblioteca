#include "Reloj.h"

#include <string>
#include <stdio.h>
#include "Utiles.h"

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef __UNIX__
#include <unistd.h>
#include <sys/time.h>
#endif

// TICKS //Calcula tiempo en base a ticks de CPU
// SEGUNDOS //Calcula tiempo en base a reloj de sistema



    CReloj::CReloj(bool segundos)
	{
	   tiempoInicial = time(NULL);
       tickstart = clock();
       segundos_o_ticks = segundos;
	}

	CReloj::~CReloj()
	{

	}

    void CReloj::reinicia_reloj()
    {
       tiempoInicial = time(NULL);
       tickstart = clock();

    }

    double CReloj::segundos_transcurridos()
    {

       tickfinish = clock();
       if (segundos_o_ticks == SEGUNDOS)
       {
          // devolver time para tiempo real
          return (double)(time(NULL) - tiempoInicial);
       }
       else
      {
          //devolver duration para ticks de CPU
          double  duration = (double)(tickfinish - tickstart) / CLOCKS_PER_SEC;
          return duration;
      }
    }

    string CReloj::tiempo_transcurrido_largo()
    {
	   string fechaHora = "";
	   char aux[128];
       double  duration = segundos_transcurridos();

       int horas = (int)(duration / 3600.0);
       int minutos = (int)((duration - horas*3600.0) / 60.0);
       int segundos = (int)(duration - horas*3600.0 - minutos*60.0);

       sprintf(aux,"%d horas, %d minutos, %d segundos",horas, minutos, segundos);

	   fechaHora = aux;

       return fechaHora;
    }

    string CReloj::tiempo_transcurrido_corto()
    {
	   string fechaHora = "";
	   char aux[128];
       double  duration = segundos_transcurridos();

       int horas = (int)(duration / 3600.0);
       int minutos = (int)((duration - horas*3600.0) / 60.0);
       int segundos = (int)(duration - horas*3600.0 - minutos*60.0);

	   if (horas<10)
		   sprintf(aux,"0%d:",horas);
	   else
		   sprintf(aux,"%d:",horas);

	   fechaHora = aux;

	   if (minutos<10)
		   sprintf(aux,"0%d:",minutos);
	   else
		   sprintf(aux,"%d:",minutos);

	   fechaHora += aux;

	   if (segundos<10)
		  sprintf(aux,"0%d",segundos);
	   else
          sprintf(aux,"%d",segundos);

	   fechaHora += aux;

       return fechaHora;
    }


    double CReloj::segundos_ahora()
    {
       if (segundos_o_ticks == SEGUNDOS)
       {
          //time devuelve segundos transcurridos del reloj
          return (double) time(NULL);
       }
       else
       {
          //clock devuelve ticks de CPU
          return (double)(clock()) / CLOCKS_PER_SEC;
       }
    }

    string CReloj::tiempo_ahora()
    {
	   string fechaHora = "";
	   char aux[128];

       time_t tiempo = (time_t) segundos_ahora();
       struct tm *ptmPtr;

       ptmPtr = localtime(&tiempo);
       strftime( aux, 80, "%H:%M:%S", ptmPtr );
	   fechaHora = aux;
       return fechaHora;
    }

    double CReloj::estima_segundos(unsigned int periodoinicial, unsigned int periodoactual, unsigned int periodofinal)
    {
	   double hecho = 0;
       double por_hacer = 0;

	   if (periodoinicial <= periodofinal)
       {
          hecho = (double)((double)periodoactual-(double)periodoinicial);
          por_hacer = (double)((double)periodofinal-(double)periodoactual);
       }
	   else
       {
          hecho = (double)((double)periodoinicial-(double)periodoactual);
          por_hacer = (double)((double)periodoactual-(double)periodofinal);
       }

	   if (hecho == 0)
		   hecho = 1;

       double tiempo_hecho = segundos_transcurridos();
       double tiempo_restante = por_hacer*tiempo_hecho/hecho;

       return tiempo_restante;
    }

    string CReloj::estima_tiempo(unsigned int periodoinicial, unsigned int periodoactual, unsigned int periodofinal)
    {
	   string fechaHora;
	   char aux[128];

       double  duration = estima_segundos(periodoinicial, periodoactual, periodofinal);

       int dias = 0;//(int) (duration / 86400.0);
       int horas = (int)((duration - dias*86400.0) / 3600.0);
       if (horas < 0)
           horas = 0;
       int minutos = (int)((duration - horas*3600.0 - dias*86400.0) / 60.0);
       if (minutos < 0)
           minutos = 0;
       int segundos = (int)(duration - dias*86400.0 - horas*3600.0 - minutos*60.0);
       if (segundos < 0)
           segundos = 0;


/*       sprintf(aux,"%d:",dias);
       fechaHora = aux;

	   if (horas<10)
		   sprintf(aux,"0%d:",horas);
	   else
*/
		   sprintf(aux,"%d:",horas);

	   fechaHora += aux;

	   if (minutos<10)
		   sprintf(aux,"0%d:",minutos);
	   else
		   sprintf(aux,"%d:",minutos);

	   fechaHora += aux;

	   if (segundos<10)
		  sprintf(aux,"0%d",segundos);
	   else
          sprintf(aux,"%d",segundos);

	   fechaHora += aux;

       return fechaHora;

    }

void CReloj::espera(int segundos)
{
    time_t start_time, cur_time;

    time(&start_time);
    do
    {
#ifdef __WIN32__
       Sleep(1000);
#endif
#ifdef __UNIX__
       sleep(1);
#endif
       time(&cur_time);
    }
    while((cur_time - start_time) < segundos);
}

string CReloj::fecha_y_hora()
{
  string aux;
  time_t tiempo;
  char fechaHora[80];
  struct tm *ptmPtr;
  tiempo = time(NULL);
  ptmPtr = localtime(&tiempo);
  strftime( fechaHora, 80, "%d/%m/%Y %H:%M:%S", ptmPtr );
  aux = fechaHora;
  return aux;
}

bool operator>(CReloj reloj, string fechahora)
{
   // Formato debe ser el devuelto por fecha_y_hora()
   string ahora = reloj.fecha_y_hora();
   // "DD/MM/AAAA#HH:MM:SS"
   //  0123456789012345678


   if (fechahora.length() != 19)
       return false;

   int dia,mes,ano,hora,minuto,segundo;
   int dia_ahora,mes_ahora,ano_ahora,hora_ahora,minuto_ahora,segundo_ahora;

   dia = texto_a_entero(fechahora.substr(0,2));
   mes = texto_a_entero(fechahora.substr(3,2));
   ano = texto_a_entero(fechahora.substr(6,4));
   hora = texto_a_entero(fechahora.substr(11,2));
   minuto = texto_a_entero(fechahora.substr(14,2));
   segundo = texto_a_entero(fechahora.substr(17,2));

   dia_ahora = texto_a_entero(ahora.substr(0,2));
   mes_ahora = texto_a_entero(ahora.substr(3,2));
   ano_ahora = texto_a_entero(ahora.substr(6,4));
   hora_ahora = texto_a_entero(ahora.substr(11,2));
   minuto_ahora = texto_a_entero(ahora.substr(14,2));
   segundo_ahora = texto_a_entero(ahora.substr(17,2));

   if ((ano_ahora > ano) ||
       (ano_ahora == ano && mes_ahora > mes) ||
       (ano_ahora == ano && mes_ahora == mes && dia_ahora > dia) ||
       (ano_ahora == ano && mes_ahora == mes && dia_ahora == dia && hora_ahora > hora) ||
       (ano_ahora == ano && mes_ahora == mes && dia_ahora == dia && hora_ahora == hora && minuto_ahora > minuto) ||
       (ano_ahora == ano && mes_ahora == mes && dia_ahora == dia && hora_ahora == hora && minuto_ahora == minuto && segundo_ahora > segundo))
       return true;

   return false;

}

unsigned int CReloj::tiempo_de_vuelo()
// Milisegundos desde la puesta en marcha del PC
{
#ifdef __WIN32__
    return (unsigned int) GetTickCount();
#endif

#ifdef __UNIX__
    timeval ts;
	gettimeofday(&ts,0);
	unsigned int milis = (unsigned int)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
	return milis;
#endif


}
