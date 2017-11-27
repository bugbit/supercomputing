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

#ifdef __cuda_cuda_h__
#define	__fastcall__
#elif !defined(__BORLANDC__) && !defined(_MSC_VER )
#define __fastcall__
#else
#define __fastcall__	_fastcall
#endif

#endif