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
				struct pixel_s sub_pixels[9]; // matriz de pixels de saída

				//int color_level = (pix_value->r + pix_value->g + pix_value->b) / 3;

				int color_level_r = determine_color_level(pix_value->r);
				int color_level_g = determine_color_level(pix_value->g);
				int color_level_b = determine_color_level(pix_value->b);
				//printf("%d %d %d\n", color_level_r, color_level_g, color_level_b);

				if (color_level_r == 1)
				{
					sub_pixels[0] = (struct pixel_s){0, 0, 0}; // todos pixels desligados
					sub_pixels[3] = (struct pixel_s){0, 0, 0};
					sub_pixels[6] = (struct pixel_s){0, 0, 0};
				}
				else if (color_level_r == 2)
				{
					sub_pixels[0] = (struct pixel_s){0, 0, 0};
					sub_pixels[3].r = pix_value->r;
					sub_pixels[3].g = pix_value->r;
					sub_pixels[3].b = pix_value->r;
					sub_pixels[6] = (struct pixel_s){0, 0, 0};
				}
				else if (color_level_r == 3) // pixel do meio desligado, demais ligados
				{
					sub_pixels[6] = *pix_value;
					sub_pixels[6] = *pix_value;
					sub_pixels[6] = *pix_value;

					sub_pixels[3] = (struct pixel_s){0, 0, 0};

					sub_pixels[0] = *pix_value;
					sub_pixels[0] = *pix_value;
					sub_pixels[0] = *pix_value;
				}
				else if (color_level_r == 4)
				{
					sub_pixels[0] = *pix_value;
					sub_pixels[0] = *pix_value;
					sub_pixels[0] = *pix_value;
					sub_pixels[3] = *pix_value;
					sub_pixels[3] = *pix_value;
					sub_pixels[3] = *pix_value;
					sub_pixels[6] = *pix_value;
					sub_pixels[6] = *pix_value;
					sub_pixels[6] = *pix_value;
				}
				if (color_level_g == 1)
				{
					sub_pixels[1] = (struct pixel_s){0, 0, 0}; // todos pixels desligados
					sub_pixels[4] = (struct pixel_s){0, 0, 0};
					sub_pixels[7] = (struct pixel_s){0, 0, 0};
				}
				else if (color_level_g == 2)
				{
					sub_pixels[1] = (struct pixel_s){0, 0, 0};
					sub_pixels[4] = *pix_value;
					sub_pixels[4] = *pix_value;
					sub_pixels[4] = *pix_value;
					sub_pixels[7] = (struct pixel_s){0, 0, 0};
				}
				else if (color_level_g == 3) // pixel do meio desligado, demais ligados
				{
					sub_pixels[1] = *pix_value;
					sub_pixels[1] = *pix_value;
					sub_pixels[1] = *pix_value;

					sub_pixels[4] = (struct pixel_s){0, 0, 0};

					sub_pixels[7] = *pix_value;
					sub_pixels[7] = *pix_value;
					sub_pixels[7] = *pix_value;
				}
				else if (color_level_g == 4)
				{
					sub_pixels[1] = *pix_value;
					sub_pixels[1] = *pix_value;
					sub_pixels[1] = *pix_value;
					sub_pixels[4] = *pix_value;
					sub_pixels[4] = *pix_value;
					sub_pixels[4] = *pix_value;
					sub_pixels[7] = *pix_value;
					sub_pixels[7] = *pix_value;
					sub_pixels[7] = *pix_value;
				}
				if (color_level_b == 1)
				{
					sub_pixels[2] = (struct pixel_s){0, 0, 0}; // todos pixels desligados
					sub_pixels[5] = (struct pixel_s){0, 0, 0};
					sub_pixels[8] = (struct pixel_s){0, 0, 0}; 
				}
				else if (color_level_b == 2)
				{
					sub_pixels[2] = (struct pixel_s){0, 0, 0};
					sub_pixels[5] = *pix_value;
					sub_pixels[5] = *pix_value;
					sub_pixels[5] = *pix_value;
					sub_pixels[8] = (struct pixel_s){0, 0, 0};
				}
				else if (color_level_b == 3) // pixel do meio desligado, demais ligados
				{
					sub_pixels[2] = *pix_value;
					sub_pixels[2] = *pix_value;
					sub_pixels[2] = *pix_value;

					sub_pixels[5] = (struct pixel_s){0, 0, 0};

					sub_pixels[8] = *pix_value;
					sub_pixels[8] = *pix_value;
					sub_pixels[8] = *pix_value;
				}
				else if (color_level_b == 4)
				{
					sub_pixels[2] = *pix_value;
					sub_pixels[2] = *pix_value;
					sub_pixels[2] = *pix_value;
					sub_pixels[5] = *pix_value;
					sub_pixels[5] = *pix_value;
					sub_pixels[5] = *pix_value;
					sub_pixels[8] = *pix_value;
					sub_pixels[8] = *pix_value;
					sub_pixels[8] = *pix_value;
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