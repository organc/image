#include "matrix.h"

Matrix* init_matrix(){
	Matrix* data = (Matrix*)malloc(sizeof(Matrix));
	memset(data, 0, sizeof(Matrix));
	return data;
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
