/* file:          lib_ppm.c
 * description:   PPM library
 * date:          03/2023
 * author:        Sergio Johann Filho <sergio.johann@acad.pucrs.br>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_ppm.h"

int read_ppm(char *file, struct image_s *image)
{
	FILE *fptr;
	char *t;
	char buf[128];
	int r, d, i, j;
	struct pixel_s *img_data;

	fptr = fopen(file, "rb");
	if (!fptr)
		return -1;

	t = fgets(buf, sizeof(buf), fptr);
	if (!t)
		goto failread;

	if (strncmp(buf, "P6\n", 3) != 0)
		goto failread;

	do
	{
		t = fgets(buf, sizeof(buf), fptr);
		if (!t)
			goto failread;

	} while (strncmp(buf, "#", 1) == 0);

	r = sscanf(buf, "%u %u", &image->width, &image->height);
	if (r < 2)
		goto failread;

	r = fscanf(fptr, "%u", &d);
	if ((r < 1) || (d != 255))
		goto failread;

	fseek(fptr, 1, SEEK_CUR);

	img_data = malloc(image->width * image->height * sizeof(struct pixel_s));
	if (!img_data)
		goto failread;

	image->pix = img_data;

	for (j = 0; j < image->height; j++)
		for (i = 0; i < image->width; i++)
			fread(&img_data[j * image->width + i], 3, 1, fptr);

	fclose(fptr);

	return 0;

failread:
	fclose(fptr);

	return -1;
}

int write_ppm(char *file, struct image_s *image)
{
	FILE *fptr;
	int i, j;

	fptr = fopen(file, "wb");
	if (!fptr)
		return -1;

	fprintf(fptr, "P6\n%d %d\n255\n", image->width, image->height);
	for (j = 0; j < image->height; j++)
		for (i = 0; i < image->width; i++)
			fwrite(&image->pix[j * image->width + i], 3, 1, fptr);

	fclose(fptr);

	return 0;
}

int new_ppm(struct image_s *image, int width, int height)
{
	struct pixel_s *img_data;

	image->width = width;
	image->height = height;

	img_data = malloc(image->width * image->height * sizeof(struct pixel_s));
	if (!img_data)
		return -1;

	image->pix = img_data;
	memset(image->pix, 0, image->width * image->height * sizeof(struct pixel_s));

	return 0;
}

int free_ppm(struct image_s *image)
{
	if (image->pix)
	{
		free(image->pix);

		return 0;
	}

	return -1;
}

int determine_color_level(struct pixel_s *pixel)
{
	//	printf("%d\n", pixel);

	if (pixel <= 74)
	{
		//		printf("1");
		return 1;
	}
	else if (pixel <= 134)
	{
		//		printf("2");
		return 2;
	}
	else if (pixel <= 179)
	{
		//		printf("3");
		return 3;
	}
	else if (pixel <= 255)
	{
		//		printf("4");
		return 4;
	}
	else
		printf("0");
	return 0;
}

int enhance_ppm(struct pixel_s *pixel, int level_r, int level_g, int level_b)
{
	switch (level_r)
	{
	case 1:
		// printf("level1!\n");
		for (int i = 0; i < 9; i++)
		{
			pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 2:
		// printf("level2!\n");
		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
			{
				pixel[i].r = 255;
				pixel[i].g = 255;
				pixel[i].b = 255;
			}
			else
				pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 3:
		// printf("level3!\n");

		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
			{
				pixel[i].r = 0;
				pixel[i].g = 0;
				pixel[i].b = 0;
			}
			else
				pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 4:
		// printf("level4!\n");
		for (int i = 0; i < 9; i++)
		{
			pixel[i].r = 255;
			pixel[i].g = 255;
			pixel[i].b = 255;
		}
	}

	switch (level_g)
	{
	case 1:
		// level 1
		for (int i = 0; i < 9; i++)
		{
			pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 2:
		// level 2
		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
			{
				pixel[i].r = 255;
				pixel[i].g = 255;
				pixel[i].b = 255;
			}
			else
				pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 3:
		// level 3
		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
			{
				pixel[i].r = 0;
				pixel[i].g = 0;
				pixel[i].b = 0;
			}
			else
				pixel[i] = (struct pixel_s){0, 0, 0};
		}

	case 4:
		// level 4
		for (int i = 0; i < 9; i++)
		{
			pixel[i].r = 255;
			pixel[i].g = 255;
			pixel[i].b = 255;
		}
	}

	switch (level_b)
	{
	case 1:
		// level 1

		for (int i = 0; i < 9; i++)
		{
			pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 2:
		// level 2
		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
			{
				pixel[i].r = 255;
				pixel[i].g = 255;
				pixel[i].b = 255;
			}
			else
				pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 3:
		// level 3
		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
			{
				pixel[i].r = 0;
				pixel[i].g = 0;
				pixel[i].b = 0;
			}
			else
				pixel[i] = (struct pixel_s){0, 0, 0};
		}
	case 4:
		// level 4
		for (int i = 0; i < 9; i++)
		{
			pixel[i].r = 255;
			pixel[i].g = 255;
			pixel[i].b = 255;
		}
	}

	return 0;
}