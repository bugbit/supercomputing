// biseccion.cpp: define el punto de entrada de la aplicación de consola.
//

#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <memory.h>
#include <time.h>

#include "ctypes.h"
#include "example.h"

int maxthreads=1000;
double threads[][2];
double retthreads[][3];

typedef struct _STACKI
{
	double2 i;
	struct _STACKI *next;
} STACKI;

static STACKI *stacki_top=NULL;
static int numsol=0;

static int _fastcall stacki_push(double x,double y)
{
	STACKI *s=(STACKI*) malloc(sizeof(STACKI));

	if (s==NULL)
	{
		perror("stacki_push error");

		return -1;
	}
	s->i.x=x;
	s->i.y=y;
	s->next=stacki_top;
	stacki_top=s;

	return 0;
}

static int _fastcall stacki_pop(double2 *i)
{
	STACKI *s=stacki_top;

	if (s==NULL)
		return -1;

	stacki_top=s->next;
	*i=s->i;
	
	free(s);
}

static int stacki_initcex_i(double2 *i,int num)
{
	for(;num-->0;i++)
		if (stacki_push(i->x,i->y))
			return -1;

	return 0;
}

static void stacki_destroy()
{
	STACKI *s=stacki_top,*tmp;

	while (s!=NULL)
	{
		tmp=s;
		s=s->next;
		free(tmp);
	}
}

static int _fastcall biseccion(double2 *i)
{
	double l=i->x,r=i->y,m,l2,r2,vl=fx(l),vr=fx(r),vm,vl2,vr2,m2=l,m22;
	
	if (csigno(vl,vr))
	{
		l2=l;r2=r;vl2=vl;vr2=vr;
		do
		{
			m22=m2;
			m2=r2-l2;
			m=(l2+r2)/2;
			vm=fx(m);
			if (vm==0)
				break;
			if (csigno(vl2,vm))
			{
				r2=m;
				vr2=vm;
			}
			else
			{
				l2=m;
				vl2=vm;
			}
		} while (m2!=m22);
		if (vm==0 || fabs(vm)<=TOLERANCIA1)
		{
			printf("x=%-15lg",m);
			if (++numsol>=F_MAXNUMSOL)
				return 1;
		}
		stacki_push(l,l2);
		stacki_push(r2,r);
	}
	else
	{
		m=(l+r)/2;
		if (m-l>TOLERANCIA1)
		{
			stacki_push(l,m);
			stacki_push(m,r);
		}
	}

	return 0;
}

int main(int argc, char * argv[])
{
	double2 i;
	time_t t1,t2;

	printf("programa que calcula las soluciones de la funcion: " FSTR "\n");
	
	if (!stacki_initcex_i(fx_iterval,sizeof(fx_iterval)/sizeof(double2)))
	{
		time(&t1);
		while (stacki_top!=NULL)
		{
			if (stacki_pop(&i))
				break;
			biseccion(&i);
		}
		time(&t2);
		stacki_destroy();
		if (numsol==0)
			printf("No he encontrado ninguna solucion");
		else if (numsol==1)
			printf("He encontrado una solucion");
		else
			printf("He encontrado %d soluciones",numsol);
		printf(" en %g segs\n",difftime(t2,t1));
		printf("Pulse tecla para salir");
		getchar();
	}

	return 0;
}

