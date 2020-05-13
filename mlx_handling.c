#include "minirt.h"
#include <mlx.h>
#include <stdlib.h>

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
			&(data->img.bpp), &(data->img.line_len), &(data->img.endian));
	printf("bpp = %d, line_len = %d, endian = %d\n", data->img.bpp, data->img.line_len, data->img.endian);
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
