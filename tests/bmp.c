#include "bmp.h"
#include "windows.h"
#include "transform.h"

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

	ReleaseDC(NULL, hdc);
}

int main(int argc, char const *argv[])
{
	if(argc >= 2){
		Matrix* data = NULL;

		data = init_matrix();
		bmp_info_print(argv[1]);
		bmp_get_matrix(argv[1], data);

		// roll_x(data);
		roll_y(data);
		// rotate_left(data);
		cut(190, 150, 250, 350, data);

		draw(data->matrix, data->width, data->height);
		free_matrix(data);
	}
	return 0;
}
