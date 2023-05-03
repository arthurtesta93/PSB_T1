#include <stdio.h>
#include "lib_ppm.h"
int main()
{

	struct image_s data;
	struct image_s *image = &data;
	int i, j, r,
		ZOOM_FACTOR = 3;

	r = read_ppm("lena.ppm", image);
	if (r == 0)
	{
		printf("width: %d, height: %d\n", image->width, image->height);
		for (j = 0; j < 2; j++)
		{

			/* 		for (i = 0; i < 10; i++)
					{
						printf("(%d %d) %d %d %d\n", i, j,
							   image->pix[j * image->width + i].r,
							   image->pix[j * image->width + i].g,
							   image->pix[j * image->width + i].b);
					} */
		}

		write_ppm("lena_copy.ppm", image);
	}

	// create information for zoomed image

	struct image_s zoom_data;
	struct image_s *zoom_image = &zoom_data;

	r = new_ppm(zoom_image, image->width * ZOOM_FACTOR, image->height * ZOOM_FACTOR);

	printf("New dimensions %d x %d", zoom_image->height, zoom_image->width);

	if (r == 0)
	{
		for (j = 0; j < image->height; j++)
		{
			for (i = 0; i < image->width; i++)
			{

				struct pixel_s *pix_value = &image->pix[j * image->width + i];
				struct pixel_s sub_pixels[9]; //matriz de pixels de saída

				int color_level = (pix_value->r + pix_value->g + pix_value->b) / 3;

				if (color_level <= 74)
				{
					for (int i = 0; i < 9; i++)
					{
						sub_pixels[i] = (struct pixel_s){0, 0, 0}; // todos pixels desligados
					}
				}
				else if (color_level <= 134)
				{
					for (int i = 0; i < 9; i++)
					{
						if (i == 4) // pixel do meio ligado, demais desligados
						{
							sub_pixels[i].r = pix_value->r;
							sub_pixels[i].g = pix_value->g;
							sub_pixels[i].b = pix_value->b;
						}
						else
						{
							sub_pixels[i] = (struct pixel_s){0, 0, 0};
						}
					}
				}
				else if (color_level <= 179) //pixel do meio desligado, demais ligados
				{
					for (int i = 0; i < 9; i++)
					{
						if (i == 4)
						{
							sub_pixels[i] = (struct pixel_s){0, 0, 0};
						}
						else
						{
							sub_pixels[i].r = pix_value->r;
							sub_pixels[i].g = pix_value->g;
							sub_pixels[i].b = pix_value->b;
						}
					}
				}
				else // mantém cores originais
				{
					for (int i = 0; i < 9; i++)
					{
						sub_pixels[i] = *pix_value;
					}
				} 
					for (int y = 0; y < 3; y++)
					{
						for (int x = 0; x < 3; x++)
						{

							int new_x = i * 3 + x;
							int new_y = j * 3 + y;
							zoom_image->pix[new_y * zoom_image->width + new_x] = *sub_pixels;
						}
					}
			}
		}

		write_ppm("with_zoom.ppm", zoom_image);
		free_ppm(image);
	}

	return 0;
}