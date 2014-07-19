#ifndef _TRANSFORN_H_
#define _TRANSFORN_H_

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "math.h"
#include "matrix.h"

/**
 * 右旋90度
 * @param matrix matrix像素矩阵
 */
void rotate_right(Matrix* matrix);

/**
 * 左旋90度
 * @param matrix matrix像素矩阵
 */
void rotate_left(Matrix* matrix);

/**
 * x轴翻转
 * @param matrix matrix像素矩阵
 */
void roll_x(Matrix* matrix);

/**
 * y轴翻转
 * @param matrix matrix像素矩阵
 */
void roll_y(Matrix* matrix);

/**
 * zoom in[放大]
 * @param matrix matrix像素矩阵
 */
void zoom_in(Matrix* matrix);

/**
 * zoom out[缩小]
 * @param matrix matrix像素矩阵
 */
void zoom_out(Matrix* matrix);

#endif
