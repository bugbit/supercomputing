#ifndef	__EXAMPLE_H__

#define	__EXAMPLE_H__

#include <math.h>

#include "ctypes.h"

#define TOLERANCIA1	1e-6
#define TOLERANCIA2	TOLERANCIA1/10.0

#define F(x) (pow(x,88)-44*pow(x,7)+22*pow(x,77)+12*pow(x,2)-1)
#define I { { -10,10 }}
#define F_MAXNUMSOL	88

#define FQ(x) #x
#define FSTR2(m) FQ(m)
#define FSTR FSTR2(F(x))

double2 fx_iterval[]=I;

__host__ __device__ double __fastcall__ fx(double x)
{
	return F(x);
}

__host__ __device__ int __fastcall__ csigno(double a,double b)
{
  if ((a<0 && b>0) || (a>0 && b<0))
	  return 1;

  return 0;
}


#endif