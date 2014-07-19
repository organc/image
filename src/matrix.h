#ifndef _MATRIX_H_
#define _MATRIX_H_

#pragma pack(push)
#pragma pack(1)

#if defined _WIN32
	typedef __int8  BYTE1;
	typedef __int16 BYTE2;
	typedef __int32 BYTE4; 
#else
	typedef int8_t  BYTE1;
	typedef int16_t BYTE2;
	typedef int32_t BYTE4;
#endif

typedef struct _RGBPx
{
	BYTE1  R;
	BYTE1  G;
	BYTE1  B;
} RGBPx;

typedef struct _Matrix
{
	size_t width;
	size_t height;
	RGBPx* matrix;
} Matrix;

#pragma pack(pop)

#endif
