#include "transform.h"

void roll_x(Matrix* matrix){
	RGBPx* tmp = NULL;
	size_t len = 0;
	size_t x = 0, y = 0, w = 0;

	len = matrix->width * matrix->height * sizeof(RGBPx);
	tmp = (RGBPx*)malloc(len);
	memset(tmp, 0, sizeof(len));
	w = matrix->width;

	for (y = 0; y < matrix->height; ++y)
	{
		for (x = 0; x < w; ++x)
		{
			tmp[y * w + x] = matrix->matrix[y * w + w - 1 - x];
		}
	}
	
	free(matrix->matrix);
	matrix->matrix = tmp;
	tmp = NULL;
}

void roll_y(Matrix* matrix){
	RGBPx* tmp = NULL;
	size_t len = 0;
	size_t x = 0, y = 0, w = 0, h = 0;

	len = matrix->width * matrix->height * sizeof(RGBPx);
	tmp = (RGBPx*)malloc(len);
	memset(tmp, 0, sizeof(len));
	w = matrix->width;
	h = matrix->height;

	for (y = 0; y < matrix->height; ++y)
	{
		for (x = 0; x < w; ++x)
		{
			tmp[y * w + x] = matrix->matrix[(h -1 - y) * w + x];
		}
	}
	
	free(matrix->matrix);
	matrix->matrix = tmp;
	tmp = NULL;
}

void rotate_right(Matrix* matrix){
	RGBPx* tmp = NULL;
	size_t len = 0;
	size_t x = 0, y = 0, w = 0, h = 0;

	len = matrix->width * matrix->height * sizeof(RGBPx);
	tmp = (RGBPx*)malloc(len);
	memset(tmp, 0, sizeof(len));
	w = matrix->width;
	h = matrix->height;

	for (y = 0; y < w; ++y)
	{
		for (x = 0; x < matrix->height; ++x)
		{
			tmp[y * h + x] =  matrix->matrix[(h - 1 - x) * w + y];
		}
	}

	matrix->width = h;
	matrix->height = w;

	free(matrix->matrix);
	matrix->matrix = tmp;
	tmp = NULL;
}

void rotate_left(Matrix* matrix){
	RGBPx* tmp = NULL;
	size_t len = 0;
	size_t x = 0, y = 0, w = 0, h = 0;

	len = matrix->width * matrix->height * sizeof(RGBPx);
	tmp = (RGBPx*)malloc(len);
	memset(tmp, 0, sizeof(len));
	w = matrix->width;
	h = matrix->height;

	for (y = 0; y < w; ++y)
	{
		for (x = 0; x < matrix->height; ++x)
		{
			tmp[x + y * h] =  matrix->matrix[( w - 1 - y) + x * w];
		}
	}

	matrix->width = h;
	matrix->height = w;

	free(matrix->matrix);
	matrix->matrix = tmp;
	tmp = NULL;
}

void cut(size_t x1, size_t y1, size_t x2, size_t y2, Matrix* matrix){
	;
}

void zoom_in(Matrix* matrix){
	;
}

void zoom_out(Matrix* matrix){
	;
}
