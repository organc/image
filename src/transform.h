#ifndef _TRANSFORN_H_
#define _TRANSFORN_H_

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "math.h"
#include "matrix.h"

void roll_x(Matrix* matrix);

void roll_y(Matrix* matrix);

void rotate_right(Matrix* matrix);

void rotate_left(Matrix* matrix);

void cut(size_t x1, size_t y1, size_t width, size_t height, Matrix* matrix);

void zoom_in(Matrix* matrix);

void zoom_out(Matrix* matrix);

#endif
