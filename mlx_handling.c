#include "minirt.h"
#include <mlx.h>
#include <stdlib.h>

void	image_pixel_put(t_global *data, int x, int y, int color)
{
	char		*pixel_pos;
	unsigned	converted_color;

	pixel_pos = data->img.addr + (y * data->img.line_len + x * (data->img.bits_per_pixel / 8));
	converted_color = (unsigned)mlx_get_color_value(data->mlx_ptr, color);
	if (data->img.endian == 0)//LITTLE_ENDIAN
	{
		*pixel_pos = (char)converted_color;
		if (data->img.bits_per_pixel >= 16)
			*(pixel_pos + 1) = (char)(converted_color >> 8);
		if (data->img.bits_per_pixel >= 24)
			*(pixel_pos + 2) = (char)(converted_color >> 16);
		if (data->img.bits_per_pixel >= 32)
			*(pixel_pos + 3) = (char)(converted_color >> 24);
	}
	else if (data->img.endian == 1) //BIG_ENDIAN
	{
		if (data->img.bits_per_pixel >= 32)
		{
			*(pixel_pos + 3) = (char)converted_color;
			*(pixel_pos + 2) = (char)(converted_color >> 8);
			*(pixel_pos + 1) = (char)(converted_color >> 16);
			*pixel_pos = (char)(converted_color >> 24);
		}
		else if (data->img.bits_per_pixel >= 24)
		{
			*(pixel_pos + 2) = (char)converted_color;
			*(pixel_pos + 1) = (char)(converted_color >> 8);
			*pixel_pos = (char)(converted_color >> 16);
		}
		else if (data->img.bits_per_pixel >= 16)
		{
			*(pixel_pos + 1) = (char)converted_color;
			*pixel_pos = (char)(converted_color >> 8);
		}
		else if (data->img.bits_per_pixel >= 8)
			*pixel_pos = (char)converted_color;
	}
}

int		close_win(int keycode, t_global *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(EXIT_SUCCESS);
	}
	return (TRUE);
}

t_bool	draw_image(t_global *data)
{
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->res[0], data->res[1]);
	data->img.addr = mlx_get_data_addr(data->img.ptr,
			&(data->img.bits_per_pixel), &(data->img.line_len), &(data->img.endian));
	printf("bpp = %d, line_len = %d, endian = %d\n", data->img.bits_per_pixel, data->img.line_len, data->img.endian);
	//mlx_get_color_value and endian
	fill_image(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (TRUE);
}

t_bool	draw_window(t_global *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FALSE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->res[0], data->res[1], "miniRT");
	draw_image(data);
	mlx_key_hook(data->win_ptr, &close_win, data);
	mlx_loop(data->mlx_ptr);
	return (TRUE);
}
