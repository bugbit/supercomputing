#ifndef	__EXAMPLE_H__

#define	__EXAMPLE_H__

#include <math.h>

#include "ctypes.h"

#define TOLERANCIA1	1e-3
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
  double va=fx(a),vb=fx(b);

  if ((va<0 && vb>0) && (va>0 && vb<0))
	  return 1;

  return 0;
}

__host__ __device__ int __fastcall__ igual(double n1,double n2) 
{
  return fabs(n1-n2)<=TOLERANCIA2;

}

__host__ __device__ int __fastcall__ igualz(double n)
{
  return igual(n,0);
}

__host__ __device__ int _fastcall fxzero(double n)
{
  return fx(n)==0;
}


#endif