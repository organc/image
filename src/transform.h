#ifndef _TRANSFORN_H_
#define _TRANSFORN_H_

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "matrix.h"
#include "common.h"

iexp void roll_x(Matrix* matrix);

iexp void roll_y(Matrix* matrix);

iexp void rotate_right(Matrix* matrix);

iexp void rotate_left(Matrix* matrix);

iexp void cut(size_t x1, size_t y1, size_t width, size_t height, Matrix* matrix);

iexp void zoom_in(Matrix* matrix);

iexp void zoom_out(Matrix* matrix);

#endif
