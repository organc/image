#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "common.h"

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

/**
 * create and initial matrix
 * @return pointer of matrix
 */
iexp Matrix* init_matrix();

/**
 * free matrix
 * @param data_matrix pointer of matrix
 */
iexp void free_matrix(Matrix* data_matrix);

#endif
