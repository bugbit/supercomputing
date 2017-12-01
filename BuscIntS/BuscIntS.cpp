#include <stdio.h>
#include <time.h>

#include "ctypes.h"
#include "example.h"

int BuscarIntSol(double a,double b)
{
	double va=fx(a),vb=fx(b),m;

	if (csigno(va,vb))
	{
		printf("[%lg,%lg]",a,b);
	}
	else
	{
		m=(a+b)/2;
		if (m-a>TOLERANCIA1)
		{
			BuscarIntSol(a,m);
			BuscarIntSol(m,b);
		}
	}

	return 0;
}

int main(int argc, char * argv[])
{
	time_t t1,t2;
	double2 *i=fx_iterval;
	int j=sizeof(fx_iterval)/sizeof(double2);

	printf("programa que calcula los intervalos de solución de la funcion: " FSTR "\n");
	for(;j-->0;i++)
	{
		BuscarIntSol(i->x,i->y);
	}
	printf("Pulse tecla para salir");
	getchar();
}