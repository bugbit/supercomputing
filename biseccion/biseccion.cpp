// biseccion.cpp: define el punto de entrada de la aplicación de consola.
//

#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <memory.h>

#include "example.h"

typedef struct _STACKI
{
	double2 i;
	struct _STACKI *next;
} STACKI;

static STACKI *stacki_top=NULL;

#include <math.h>
#include "ctypes.h"
#include "example.h"

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

static int _fastcall biseccion(double2 *i)
{
	bool sol=0;
	double l=i->x,r=i->y,s,m;

	for(;i->x<=i->y;)
	{
		if (csigno(l,r))
		{
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
				stacki_push(m,r);
				r=m;
			}
			else if (csigno(m,r))
			{				
				stacki_push(l,m);
				l=m;
			}
			else
			{
				stacki_push(l,m);
				stacki_push(l,m);
				break;
			}
		}
	}
	if (sol)
		printf("x=%-15lg",s);

	return 0;
}

int main(int argc, char * argv[])
{
	double2 i;

	printf("programa que calcula las soluciones de la función: " FSTR "\n");
	
	if (!stacki_initcex_i(fx_iterval,sizeof(fx_iterval)/sizeof(double2)))
	{
		while (stacki_top!=NULL)
		{
			if (stacki_pop(&i))
				break;
			biseccion(&i);
		}
	}

	return 0;
}

