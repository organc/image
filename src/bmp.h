#ifndef _BMP_H_
#define _BMP_H_ 

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

#if defined _WIN32
	typedef __int8  BYTE1;
	typedef __int16 BYTE2;
	typedef __int32 BYTE4; 
#else
	typedef int8_t  BYTE1;
	typedef int16_t BYTE2;
	typedef int32_t BYTE4;
#endif

#pragma pack(push)
#pragma pack(1)

typedef struct _BITMAPFILEHEADER
{
	BYTE2  bfType;
	BYTE4  bfSize;
	BYTE2  bfReserved1;
	BYTE2  bfReserved2;
	BYTE4  bfOffBits;
} BitmapFileHeader;

typedef struct _BITMAPINFOHEADER{ 
	BYTE4  biSize;
	BYTE4  biWidth;
	BYTE4  biHeight;
	BYTE2  biPlanes;
	BYTE2  biBitCount;
	BYTE4  biCompression;
	BYTE4  biSizeImage;
	BYTE4  biXPelsPerMeter;
	BYTE4  biYPelsPerMeter;
	BYTE4  biClrUsed;
	BYTE4  biClrImportant;
} BitmapInfoHeader;

typedef struct _RGBQUAD {
	BYTE1  rgbBlue;
	BYTE1  rgbGreen;
	BYTE1  rgbRed;
	BYTE1  rgbReserved;
} RGBQuad;

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
Matrix* init_matrix();

/**
 * get matrix
 * @param  image_path  image file path
 * @param  data_matrix pointer of matrix
 * @return             pointer of matrix
 */
Matrix* bmp_get_matrix(const char* image_path, Matrix* data_matrix);

/**
 * free matrix
 * @param data_matrix pointer of matrix
 */
void free_matrix(Matrix* data_matrix);

/**
 * print the headers of bmp file
 * @param image_path file path
 */
void bmp_info_print(const char* image_path);

#endif
