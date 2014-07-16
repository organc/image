#include "bmp.h"
#include <windows.h>

void draw(BYTE1* data, size_t width, size_t height){
	HDC hdc = NULL;
	size_t x = 0, y = 0, data_size_per_line = 0;

	data_size_per_line = (width*3+3)/4*4;
	hdc = GetDC(NULL);
	
	for (y = 0; y < height; ++y)
	{
		for (x = 0; x < width; ++x)
		{
			SetPixel(hdc, x, y, RGB(data[y*data_size_per_line+3*x+2] , data[y*data_size_per_line+3*x+1] ,  data[y*data_size_per_line+3*x]));
		}
	}
}

void img_read(const char* image_path){
	size_t len_file_header = 0;
	size_t len_info_header = 0;
	size_t len_info_data = 0;
	size_t data_size_per_line = 0;
	BitmapFileHeader* bitmap_file_header_buffer = NULL;
	BitmapInfoHeader* bitmap_info_header_buffer = NULL;
	FILE *fp = NULL;
	BYTE1* data = NULL;

	fp = fopen(image_path, "rb");

	len_file_header = sizeof(BitmapFileHeader);
	bitmap_file_header_buffer = (BitmapFileHeader*) malloc(len_file_header);
	memset(bitmap_file_header_buffer, 0, len_file_header);

	fread(bitmap_file_header_buffer, len_file_header, 1, fp);

	printf("===========================\n");
	printf("bfType: %d[%p]\n", bitmap_file_header_buffer->bfType, bitmap_file_header_buffer->bfType);
	printf("bfSize: %ld[%p]\n", bitmap_file_header_buffer->bfSize, bitmap_file_header_buffer->bfSize);
	printf("bfReserved1: %d[%p]\n", bitmap_file_header_buffer->bfReserved1, bitmap_file_header_buffer->bfReserved1);
	printf("bfReserved2: %d[%p]\n", bitmap_file_header_buffer->bfReserved2, bitmap_file_header_buffer->bfReserved2);
	printf("bfOffBits: %ld[%p]\n", bitmap_file_header_buffer->bfOffBits, bitmap_file_header_buffer->bfOffBits);

	len_info_header = sizeof(BitmapInfoHeader);
	bitmap_info_header_buffer = (BitmapInfoHeader*) malloc(len_info_header);
	memset(bitmap_info_header_buffer, 0, len_info_header);

	fread(bitmap_info_header_buffer, len_info_header, 1, fp);

	printf("===========================\n");
	printf("biSize: %d[%p]\n", bitmap_info_header_buffer->biSize, bitmap_info_header_buffer->biSize);
	printf("biWidth: %d[%p]\n", bitmap_info_header_buffer->biWidth, bitmap_info_header_buffer->biWidth);
	printf("biHeight: %d[%p]\n", bitmap_info_header_buffer->biHeight, bitmap_info_header_buffer->biHeight);
	printf("biPlanes: %d[%p]\n", bitmap_info_header_buffer->biPlanes, bitmap_info_header_buffer->biPlanes);
	printf("biBitCount: %d[%p]\n", bitmap_info_header_buffer->biBitCount, bitmap_info_header_buffer->biBitCount);
	printf("biCompression: %d[%p]\n", bitmap_info_header_buffer->biCompression, bitmap_info_header_buffer->biCompression);
	printf("biSizeImage: %d[%p]\n", bitmap_info_header_buffer->biSizeImage, bitmap_info_header_buffer->biSizeImage);
	printf("biXPelsPerMeter: %d[%p]\n", bitmap_info_header_buffer->biXPelsPerMeter, bitmap_info_header_buffer->biXPelsPerMeter);
	printf("biYPelsPerMeter: %d[%p]\n", bitmap_info_header_buffer->biYPelsPerMeter, bitmap_info_header_buffer->biYPelsPerMeter);
	printf("biClrUsed: %d[%p]\n", bitmap_info_header_buffer->biClrUsed, bitmap_info_header_buffer->biClrUsed);
	printf("biClrImportant: %d[%p]\n", bitmap_info_header_buffer->biClrImportant, bitmap_info_header_buffer->biClrImportant);

	printf("===========================\n");
	if (bitmap_file_header_buffer->bfOffBits - 54 < 0){
		printf("mode: %s\n", "ERROR!");
	}else if(bitmap_file_header_buffer->bfOffBits - 54 == 0){
		printf("mode: %s\n", "rgb");
	}else if(bitmap_file_header_buffer->bfOffBits - 54 > 0){
		printf("mode: %s\n", "index");
	}

	data_size_per_line = (bitmap_info_header_buffer->biWidth* bitmap_info_header_buffer->biBitCount+31)/8;
	len_info_data = sizeof(BYTE1) * data_size_per_line * bitmap_info_header_buffer->biHeight;
	data = (BYTE1*)malloc(len_info_data);
	memset(data, 0, len_info_data);
	fread(data, sizeof(BYTE1) * data_size_per_line, bitmap_info_header_buffer->biHeight, fp);
	draw(data, bitmap_info_header_buffer->biWidth, bitmap_info_header_buffer->biHeight);
}



int main(int argc, char const *argv[])
{
	if(argc >= 2){
		img_read(argv[1]);
		
	}
	return 0;
}
