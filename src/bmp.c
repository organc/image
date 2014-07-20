#include "bmp.h"

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
	int tab_num = 0;
	RGBQuad* tab = NULL;

	fp = fopen(image_path, "rb");
	len_file_hdr = sizeof(BitmapFileHeader);
	file_hdr_buf = (BitmapFileHeader*) malloc(len_file_hdr);
	memset(file_hdr_buf, 0, len_file_hdr);
	fread(file_hdr_buf, len_file_hdr, 1, fp);
	len_info_hdr = sizeof(BitmapInfoHeader);
	info_hdr_buf = (BitmapInfoHeader*) malloc(len_info_hdr);
	memset(info_hdr_buf, 0, len_info_hdr);
	fread(info_hdr_buf, len_info_hdr, 1, fp);

	memset(data_matrix, 0, sizeof(Matrix));
	data_matrix->width = info_hdr_buf->biWidth;
	data_matrix->height = info_hdr_buf->biHeight;

	if (info_hdr_buf->biBitCount == 1){
		if (info_hdr_buf->biWidth % (8 * 4) == 0)
		{
			data_size_per_line = info_hdr_buf->biWidth / (8 * 4) * 4;
		}else{
			data_size_per_line = (info_hdr_buf->biWidth / (8 * 4) + 1) * 4;
		}
	}else if (info_hdr_buf->biBitCount == 4){
		if (info_hdr_buf->biWidth % (2 * 4) == 0)
		{
			data_size_per_line = info_hdr_buf->biWidth / (2 * 4) * 4;
		}else{
			data_size_per_line = (info_hdr_buf->biWidth / (2 * 4) + 1) * 4;
		}
	}else if (info_hdr_buf->biBitCount == 8){
		if (info_hdr_buf->biWidth % (1 * 4) == 0)
		{
			data_size_per_line = info_hdr_buf->biWidth / (1 * 4) * 4;
		}else{
			data_size_per_line = (info_hdr_buf->biWidth / (1 * 4) + 1) * 4;
		}
	}else if (info_hdr_buf->biBitCount == 24){
		if ((info_hdr_buf->biWidth * 3) % 4 == 0)
		{
			data_size_per_line = (info_hdr_buf->biWidth * info_hdr_buf->biBitCount / 8) / 4 * 4;
		}else{
			data_size_per_line = (info_hdr_buf->biWidth * info_hdr_buf->biBitCount / 8) / 4 * 4 + 4;
		}
	}

	// read color table
	if (info_hdr_buf->biBitCount != 24)
	{
		tab_num = (int)pow(2, info_hdr_buf->biBitCount);
		tab = (RGBQuad*)malloc(sizeof(RGBQuad)*tab_num);
		memset(tab, 0, sizeof(RGBQuad)*tab_num);
		fread(tab, sizeof(RGBQuad), tab_num, fp);
	}

	len_info_data = sizeof(BYTE1) * data_size_per_line * info_hdr_buf->biHeight;
	data = (BYTE1*)malloc(len_info_data);
	memset(data, 0, len_info_data);
	// fseek(fp, file_hdr_buf->bfOffBits, SEEK_SET);
	fread(data, sizeof(BYTE1) * data_size_per_line, info_hdr_buf->biHeight, fp);
	matrix_len = info_hdr_buf->biWidth * info_hdr_buf->biHeight * 3;
	matrix = (RGBPx*)malloc(matrix_len);
	memset(matrix, 0, matrix_len);

	if (info_hdr_buf->biBitCount == 24)
	{
		for (y = 0; y < info_hdr_buf->biHeight; ++y)
		{
			for (x = 0; x < info_hdr_buf->biWidth; ++x)
			{
				matrix[y*info_hdr_buf->biWidth+x].R = data[y*data_size_per_line+3*x+2];
				matrix[y*info_hdr_buf->biWidth+x].G = data[y*data_size_per_line+3*x+1];
				matrix[y*info_hdr_buf->biWidth+x].B = data[y*data_size_per_line+3*x+3];
			}
		}
	}else{
		int tab_index = 0;
		BYTE1 tmp_byte = 0;
		BYTE2 tmp_byte2 = 0;
		int b1_i = 0;
		int b1_m = 0;

		for (y = 0; y < info_hdr_buf->biHeight; ++y)
		{
			for (x = 0; x < info_hdr_buf->biWidth; ++x)
			{
				// get color table index
				if (info_hdr_buf->biBitCount == 8)
				{
					tmp_byte = data[y*data_size_per_line + x];  // here is a trap
					memset(&tmp_byte2,tmp_byte,1);
					tab_index = tmp_byte2;
				}else if (info_hdr_buf->biBitCount == 4)
				{
					tmp_byte = data[y*data_size_per_line + x / 2];
					tab_index = (x % 2 == 0)?(tmp_byte & 0x0f):((tmp_byte & 0xf0) >> 4);
				}else if (info_hdr_buf->biBitCount == 1)
				{
					b1_i = x / 8;
					b1_m = x % 8;
					tmp_byte = data[y*data_size_per_line + x / 8];

					if (b1_m == 0)
					{
						tab_index = (tmp_byte & 0x01) >> 0;
					}else if (b1_m == 1)
					{
						tab_index = (tmp_byte & 0x80) >> 7;
					}else if (b1_m == 2)
					{
						tab_index = (tmp_byte & 0x40) >> 6;
					}else if (b1_m == 3)
					{
						tab_index = (tmp_byte & 0x20) >> 5;
					}else if (b1_m == 4)
					{
						tab_index = (tmp_byte & 0x10) >> 4;
					}else if (b1_m == 5)
					{
						tab_index = (tmp_byte & 0x08) >> 3;
					}else if (b1_m == 6)
					{
						tab_index = (tmp_byte & 0x04) >> 2;
					}else if (b1_m == 7)
					{
						tab_index = (tmp_byte & 0x02) >> 1;
					}
				}

				matrix[y*info_hdr_buf->biWidth+x].R = tab[tab_index].rgbRed;
				matrix[y*info_hdr_buf->biWidth+x].G = tab[tab_index].rgbGreen;
				matrix[y*info_hdr_buf->biWidth+x].B = tab[tab_index].rgbBlue;
			}
		}

		free(tab);
		tab = NULL;
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
	if(info_hdr_buf->biBitCount == 24){
		printf("mode: %s\n", "rgb");
	}else if((info_hdr_buf->biBitCount == 1)||(info_hdr_buf->biBitCount == 4)||(info_hdr_buf->biBitCount == 8)){
		printf("mode: %s\n", "index");
	}else{
		printf("mode: %s\n", "ERROR!");
	}

	// read color table and check alpha channel
	if (info_hdr_buf->biBitCount != 24)
	{
		RGBQuad* tab = NULL;
		int tab_num = 0;
		int i = 0;
		int used_colors = 0;

		tab_num = (int)pow(2, info_hdr_buf->biBitCount);
		tab = (RGBQuad*)malloc(sizeof(RGBQuad)*tab_num);
		memset(tab, 0, sizeof(RGBQuad)*tab_num);
		fread(tab, sizeof(RGBQuad), tab_num, fp);

		used_colors = (info_hdr_buf->biClrUsed == 0)?(tab_num):(info_hdr_buf->biClrUsed);
		for (i = 0; i < used_colors; ++i)
		{
			if(tab[i].rgbReserved){
				printf("Warning: alpha channel contained in (%d)!\n", i);
				break;
			}
		}

		free(tab);
		tab = NULL;
		
	}

	fclose(fp);
	free(file_hdr_buf);
	free(info_hdr_buf);
	file_hdr_buf = NULL;
	info_hdr_buf = NULL;
}


