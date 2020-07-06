/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:40:18 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:18:58 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_management.h"

void		pixel_put_bmp_little_endian(char *pixel_pos, int color)
{
	pixel_pos[0] = (char)color;
	pixel_pos[1] = (char)(color >> 8);
	pixel_pos[2] = (char)(color >> 16);
}

void		uint_to_str_little_endian(unsigned nb, char *str)
{
	str[0] = (char)nb;
	str[1] = (char)(nb >> 8);
	str[2] = (char)(nb >> 16);
	str[3] = (char)(nb >> 24);
}

static void	pixel_put_mlx_big_endian(t_mlx_image *image, char *pixel_pos,
		unsigned color)
{
	if (image->bits_per_pixel >= 32)
	{
		*(pixel_pos + 3) = (char)color;
		*(pixel_pos + 2) = (char)(color >> 8);
		*(pixel_pos + 1) = (char)(color >> 16);
		*pixel_pos = (char)(color >> 24);
	}
	else if (image->bits_per_pixel >= 24)
	{
		*(pixel_pos + 2) = (char)color;
		*(pixel_pos + 1) = (char)(color >> 8);
		*pixel_pos = (char)(color >> 16);
	}
	else if (image->bits_per_pixel >= 16)
	{
		*(pixel_pos + 1) = (char)color;
		*pixel_pos = (char)(color >> 8);
	}
	else if (image->bits_per_pixel >= 8)
		*pixel_pos = (char)color;
}

void		pixel_put_mlx_image(t_mlx_image *image, size_t x, size_t y,
		unsigned color)
{
	char		*pixel_pos;

	pixel_pos = image->addr + ((int)y * image->line_len +
			(int)x * (image->bits_per_pixel / 8));
	if (image->endian == LITTLE_ENDIAN_)
	{
		*pixel_pos = (char)color;
		if (image->bits_per_pixel >= 16)
			*(pixel_pos + 1) = (char)(color >> 8);
		if (image->bits_per_pixel >= 24)
			*(pixel_pos + 2) = (char)(color >> 16);
		if (image->bits_per_pixel >= 32)
			*(pixel_pos + 3) = (char)(color >> 24);
	}
	else if (image->endian == BIG_ENDIAN_)
		pixel_put_mlx_big_endian(image, pixel_pos, color);
}
