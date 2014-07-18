#include "bmp.h"

Matrix* init_matrix(){
	Matrix* data = (Matrix*)malloc(sizeof(Matrix));
	memset(data, 0, sizeof(Matrix));
	return data;
}

Matrix* bmp_get_matrix(const char* image_path, Matrix* data_matrix){
	size_t len_file_hdr = 0;
	size_t len_info_hdr = 0;
	size_t len_info_data = 0;
	size_t data_size_per_line = 0;
	BitmapFileHeader* file_hdr_buf = NULL;
	BitmapInfoHeader* info_hdr_buf = NULL;
	FILE *fp = NULL;
	BYTE1* data = NULL;
	size_t matrix_len = 0;
	int x = 0, y = 0;
	RGBPx* matrix = NULL;

	fp = fopen(image_path, "rb");
	len_file_hdr = sizeof(BitmapFileHeader);
	file_hdr_buf = (BitmapFileHeader*) malloc(len_file_hdr);
	memset(file_hdr_buf, 0, len_file_hdr);
	fread(file_hdr_buf, len_file_hdr, 1, fp);
	len_info_hdr = sizeof(BitmapInfoHeader);
	info_hdr_buf = (BitmapInfoHeader*) malloc(len_info_hdr);
	memset(info_hdr_buf, 0, len_info_hdr);
	fread(info_hdr_buf, len_info_hdr, 1, fp);

	if (file_hdr_buf->bfOffBits - 54 < 0){
		return NULL;
	}else if(file_hdr_buf->bfOffBits - 54 == 0){
	}else if(file_hdr_buf->bfOffBits - 54 > 0){
		return NULL;
	}

	memset(data_matrix, 0, sizeof(Matrix));
	data_matrix->width = info_hdr_buf->biWidth;
	data_matrix->height = info_hdr_buf->biHeight;

	if ((info_hdr_buf->biWidth * 3) % 4 == 0)
	{
		data_size_per_line = (info_hdr_buf->biWidth * info_hdr_buf->biBitCount / 8) / 4 * 4;
	}else{
		data_size_per_line = (info_hdr_buf->biWidth * info_hdr_buf->biBitCount / 8) / 4 * 4 + 4;
	}
	
	len_info_data = sizeof(BYTE1) * data_size_per_line * info_hdr_buf->biHeight;
	data = (BYTE1*)malloc(len_info_data);
	memset(data, 0, len_info_data);
	fread(data, sizeof(BYTE1) * data_size_per_line, info_hdr_buf->biHeight, fp);
	matrix_len = info_hdr_buf->biWidth * info_hdr_buf->biHeight * 3;
	matrix = (RGBPx*)malloc(matrix_len);
	memset(matrix, 0, matrix_len);
	for (y = 0; y < info_hdr_buf->biHeight; ++y)
	{
		for (x = 0; x < info_hdr_buf->biWidth; ++x)
		{
			matrix[y*info_hdr_buf->biWidth+x].R = data[y*data_size_per_line+3*x+2];
			matrix[y*info_hdr_buf->biWidth+x].G = data[y*data_size_per_line+3*x+1];
			matrix[y*info_hdr_buf->biWidth+x].B = data[y*data_size_per_line+3*x+3];
		}
	}

	fclose(fp);
	free(data);
	free(file_hdr_buf);
	free(info_hdr_buf);
	data = NULL;
	file_hdr_buf = NULL;
	info_hdr_buf = NULL;
	data_matrix->matrix = matrix;

	return data_matrix;
}

void free_matrix(Matrix* data_matrix){
	if (data_matrix->matrix != NULL)
	{
		free(data_matrix->matrix);
		data_matrix->matrix = NULL;
	}
	
	if (data_matrix != NULL)
	{
		free(data_matrix);
		data_matrix = NULL;
	}
	
}

void bmp_info_print(const char* image_path){
	size_t len_file_hdr = 0;
	size_t len_info_hdr = 0;
	size_t len_info_data = 0;
	size_t data_size_per_line = 0;
	BitmapFileHeader* file_hdr_buf = NULL;
	BitmapInfoHeader* info_hdr_buf = NULL;
	FILE *fp = NULL;
	BYTE1* data = NULL;
	size_t matrix_len = 0;
	int x = 0, y = 0;
	RGBPx* matrix = NULL;

	fp = fopen(image_path, "rb");

	len_file_hdr = sizeof(BitmapFileHeader);
	file_hdr_buf = (BitmapFileHeader*) malloc(len_file_hdr);
	memset(file_hdr_buf, 0, len_file_hdr);

	fread(file_hdr_buf, len_file_hdr, 1, fp);

	printf("===========================\n");
	printf("bfType: %d[%p]\n", file_hdr_buf->bfType, file_hdr_buf->bfType);
	printf("bfSize: %ld[%p]\n", file_hdr_buf->bfSize, file_hdr_buf->bfSize);
	printf("bfReserved1: %d[%p]\n", file_hdr_buf->bfReserved1, file_hdr_buf->bfReserved1);
	printf("bfReserved2: %d[%p]\n", file_hdr_buf->bfReserved2, file_hdr_buf->bfReserved2);
	printf("bfOffBits: %ld[%p]\n", file_hdr_buf->bfOffBits, file_hdr_buf->bfOffBits);

	len_info_hdr = sizeof(BitmapInfoHeader);
	info_hdr_buf = (BitmapInfoHeader*) malloc(len_info_hdr);
	memset(info_hdr_buf, 0, len_info_hdr);

	fread(info_hdr_buf, len_info_hdr, 1, fp);

	printf("===========================\n");
	printf("biSize: %d[%p]\n", info_hdr_buf->biSize, info_hdr_buf->biSize);
	printf("biWidth: %d[%p]\n", info_hdr_buf->biWidth, info_hdr_buf->biWidth);
	printf("biHeight: %d[%p]\n", info_hdr_buf->biHeight, info_hdr_buf->biHeight);
	printf("biPlanes: %d[%p]\n", info_hdr_buf->biPlanes, info_hdr_buf->biPlanes);
	printf("biBitCount: %d[%p]\n", info_hdr_buf->biBitCount, info_hdr_buf->biBitCount);
	printf("biCompression: %d[%p]\n", info_hdr_buf->biCompression, info_hdr_buf->biCompression);
	printf("biSizeImage: %d[%p]\n", info_hdr_buf->biSizeImage, info_hdr_buf->biSizeImage);
	printf("biXPelsPerMeter: %d[%p]\n", info_hdr_buf->biXPelsPerMeter, info_hdr_buf->biXPelsPerMeter);
	printf("biYPelsPerMeter: %d[%p]\n", info_hdr_buf->biYPelsPerMeter, info_hdr_buf->biYPelsPerMeter);
	printf("biClrUsed: %d[%p]\n", info_hdr_buf->biClrUsed, info_hdr_buf->biClrUsed);
	printf("biClrImportant: %d[%p]\n", info_hdr_buf->biClrImportant, info_hdr_buf->biClrImportant);

	printf("===========================\n");
	if (file_hdr_buf->bfOffBits - 54 < 0){
		printf("mode: %s\n", "ERROR!");
		return;
	}else if(file_hdr_buf->bfOffBits - 54 == 0){
		printf("mode: %s\n", "rgb");
	}else if(file_hdr_buf->bfOffBits - 54 > 0){
		printf("mode: %s\n", "index");
		return;
	}

	fclose(fp);
	free(file_hdr_buf);
	free(info_hdr_buf);
	file_hdr_buf = NULL;
	info_hdr_buf = NULL;
}


