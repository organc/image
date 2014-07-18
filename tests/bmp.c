#include "bmp.h"
#include "windows.h"

void draw(RGBPx* data, size_t width, size_t height){
	HDC hdc = NULL;
	size_t x = 0, y = 0;

	hdc = GetDC(NULL);
	
	for (y = 0; y < height; ++y)
	{
		for (x = 0; x < width; ++x)
		{
			SetPixel(hdc, x, y, RGB(data[y*width+x].R , data[y*width+x].G ,  data[y*width+x].B));
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc >= 2){
		Matrix* data = NULL;

		data = init_matrix();
		bmp_info_print(argv[1]);
		bmp_get_matrix(argv[1], data);
		draw(data->matrix, data->width, data->height);
		free_matrix(data);
	}
	return 0;
}
