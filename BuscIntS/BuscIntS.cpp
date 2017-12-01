#include <stdio.h>
#include <time.h>

#include "ctypes.h"
#include "example.h"

int BuscarIntSol(double a,double b)
{
	double va=fx(a),vb=fx(b),m,vm;
	double a2,b2,va2,vb2;
	int crece,crece2,n;
	double dc,dc2;

	if (csigno(va,vb))
	{
		crece=va<vb;
		dc=(vb-va)/(b-a);
		a2=a;
		b2=b;
		va2=va;
		vb2=vb;
		n=1;
		for (;b2-a2>TOLERANCIA1;n++)
		{			
			m=(a2+b2)/2;
			vm=fx(m);
			crece2=vm<vb2;
			if (!csigno(va2,vm))
			{
				if (m-a<=TOLERANCIA1)
					break;
				a2=m;
				va2=vm;
			}
			else
			{
				if (crece!=crece2)
				{
					a2=m;
					va2=vm;
				}
				else
				{
					b2=m;
					vb2=vm;
				}
			}
			dc2=(vb2-va2)/(b2-a2);
			if (dc/n<=dc2)
				break;
			dc += dc2;
		}
		if (a2-a>TOLERANCIA1)
			BuscarIntSol(a,a2);
		printf("[%lg,%lg]\t",a2,b2);
		if (b-b2>TOLERANCIA1)
			BuscarIntSol(b2,b);
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