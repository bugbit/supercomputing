#ifndef	__EXAMPLE_H__

#define	__EXAMPLE_H__

#include <math.h>

#include "ctypes.h"

#define TOLERANCIA1	1e-3
#define TOLERANCIA2	TOLERANCIA1/10.0

#define F(x) (pow(x,88)-44*pow(x,7)+22*pow(x,77)+12*pow(x,2)-1)
#define FQ(x) #x
#define FSTR2(m) FQ(m)
#define FSTR FSTR2(F(x))

#define I { { -10,10 }}

double2 fx_iterval[]=I;

__host__ __device__ double _fastcall fx(double x)
{
	return F(x);
}

__host__ __device__ int _fastcall csigno(double a,double b)
{
  return (fx(a)*fx(b))<=0;
}

__host__ __device__ int _fastcall igual(double n1,double n2) 
{
  return fabs(n1-n2)<=TOLERANCIA2;

}

__host__ __device__ int _fastcall igualz(double n)
{
  return igual(n,0);
}

__host__ __device__ int _fastcall fxzero(double n)
{
  return igualz(fx(n));
}


#endif