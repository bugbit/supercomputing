#ifndef	__CTYPES_H__

#define	__CTYPES_H__

#ifndef __cuda_cuda_h__

#define	__global__
#define __host__ 
#define __device__

typedef struct
{
	double x,y;
} double2;

#endif

#if !defined(__BORLANDC__) && !defined(_MSC_VER )
#define _fastcall
#endif

#endif