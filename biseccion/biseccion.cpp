// biseccion.cpp: define el punto de entrada de la aplicación de consola.
//

#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <memory.h>
#include <time.h>

#include "ctypes.h"
#include "example.h"

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
	bool sol=0;
	double l=i->x,r=i->y,s,m,l2,r2;

	for(;l<r;)
	{
		if (csigno(l,r))
		{
			for(l2=l,r2=r;!igual(l2,r2);)
			{				
				m=(l2+r2)/2;
				if (fxzero(m))
					break;
				if (csigno(l2,m))
				{
					r2=m;
				}
				else if (csigno(m,r2))
				{
					l2=m;
				}
			}
			s=m;
			sol=1;
			stacki_push(l,l2-TOLERANCIA1);
			stacki_push(r2+TOLERANCIA1,r);
			break;
		}
		else
		{
			if (fxzero(l))
			{
				s=l;
				sol=1;
				break;
			}
			if (fxzero(r))
			{
				s=r;
				sol=1;
				break;
			}
			m=(l+r)/2;
			if (fxzero(m))
			{
				s=i->y;
				sol=1;
				break;
			}
			if (csigno(l,m))
			{
				r=m;
				stacki_push(m,r);
			}
			else if (csigno(m,r))
			{
				l=m;				
				stacki_push(l,m);
			}
			else
			{
				r=m;
				stacki_push(m,r);
			}
		}
	}
	if (sol)
	{
		printf("x=%-15lg",s);
		if (++numsol>=F_MAXNUMSOL)
			return 1;
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
	}

	return 0;
}

