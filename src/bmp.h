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
} BITMAPFILEHEADER;

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
} BITMAPINFOHEADER;

typedef struct _RGBQUAD {
	BYTE1  rgbBlue;
	BYTE1  rgbGreen;
	BYTE1  rgbRed;
	BYTE1  rgbReserved;
} RGBQUAD;

#pragma pack(pop)
