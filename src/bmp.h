#ifndef _BMP_H_
#define _BMP_H_ 

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "math.h"
#include "matrix.h"
#include "common.h"

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

#pragma pack(pop)

/**
 * get matrix
 * @param  image_path  image file path
 * @param  data_matrix pointer of matrix
 * @return             pointer of matrix
 */
iexp Matrix* bmp_get_matrix(const char* image_path, Matrix* data_matrix);

/**
 * print the headers of bmp file
 * @param image_path file path
 */
iexp void bmp_info_print(const char* image_path);

#endif
