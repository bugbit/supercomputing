#include <stdio.h>
#include <time.h>

#include "ctypes.h"
#include "example.h"

int BuscarIntSol(double a,double b)
{
	double va=fx(a),vb=fx(b),m,vm;
	double a2,b2,va2,vb2;

	if (csigno(va,vb))
	{
		a2=a;
		b2=b;
		va2=va;
		vb2=vb;
		do
		{			
			m=(a2+b2)/2;
			vm=fx(m);
			if (!csigno(va2,vm))
			{				
				if (m-a2<=TOLERANCIA2)
					break;
				a2=m;
				va2=vm;
			}
			else
			{
				if (b2-m<=TOLERANCIA2)
					break;
				b2=m;
				vb2=vm;
			}
		} while(b2-a2>TOLERANCIA2);
		if (a2-a>TOLERANCIA2)
			BuscarIntSol(a,a2);
		printf("[%lg,%lg] m: %lg va: %lg vm: %lg vb: %lg\n",a2,b2,m,va2,vm,vb2);
		if (b-b2>TOLERANCIA2)
			BuscarIntSol(b2,b);
	}
	else
	{
		m=(a+b)/2;
		if (m-a>TOLERANCIA1)
			BuscarIntSol(a,m);
		if (b-m>TOLERANCIA1)
			BuscarIntSol(m,b);
	}

	return 0;
}

int main(int argc, char * argv[])
{
	time_t t1,t2;
	double2 *i=fx_iterval;
	int j=sizeof(fx_iterval)/sizeof(double2);

	printf("-1.013776, -0.287639, 0.289762, 0.746586, 1.005253\n");
	printf("programa que calcula los intervalos de solución de la funcion: " FSTR "\n");
	for(;j-->0;i++)
	{
		BuscarIntSol(i->x,i->y);
	}
	printf("Pulse tecla para salir");
	getchar();
}