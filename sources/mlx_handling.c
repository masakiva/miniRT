/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:00:45 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:39:07 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_handling.h"

unsigned	convert_color(void *mlx_ptr, int color)
{
	return ((unsigned)mlx_get_color_value(mlx_ptr, color));
}

void	check_resolution(t_global *data)
{
	int		screen_width;
	int		screen_height;

	errno = 0;
	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	if (screen_width <= 0 || screen_height <= 0)
		error_and_exit(MLX_SCREEN_SIZE_ERROR);
	if (data->res[WIDTH] == 0 || data->res[WIDTH] > (size_t)screen_width)
		data->res[WIDTH] = (size_t)screen_width;
	if (data->res[HEIGHT] == 0 || data->res[HEIGHT] > (size_t)screen_height)
		data->res[HEIGHT] = (size_t)screen_height;
}

t_image	*new_image(t_global *data)
{
	t_image	*new_image;

	errno = 0;
	new_image = (t_image *)malloc(sizeof(t_image));
	if (new_image == NULL)
		return (NULL);
	errno = 0;
	if (add_to_list(new_image, &(data->images)) == FAILURE)
		return (NULL);
	errno = 0;
	new_image->ptr = mlx_new_image(data->mlx_ptr,
			(int)data->res[WIDTH], (int)data->res[HEIGHT]);
	if (new_image->ptr == NULL)
	{
		free_data(data);
		error_and_exit(MLX_NEW_IMAGE_ERROR);
	}
	new_image->addr = mlx_get_data_addr(new_image->ptr,
			&(new_image->bits_per_pixel), &(new_image->line_len),
			&(new_image->endian));
	return (new_image);
}

t_bool	draw_images(t_global *data)
{
	t_list	*cameras_iter;
	t_image	*cur_image;

	cameras_iter = data->cameras;
	while (cameras_iter != NULL)
	{
		cur_image = new_image(data);
		if (cur_image == NULL)
			error_and_exit(MALLOC_ERROR);
		fill_mlx_image(data, cur_image, (t_camera *)cameras_iter->content);
		cameras_iter = cameras_iter->next;
	}
	return (SUCCESS);
}

void	render_with_mlx(t_global *data)
{
	errno = 0;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		free_data(data);
		error_and_exit(MLX_INIT_ERROR);
	}
	check_resolution(data);
	draw_images(data);
	errno = 0;
	data->win_ptr = mlx_new_window(data->mlx_ptr, (int)data->res[WIDTH],
			(int)data->res[HEIGHT], MLX_WINDOW_TITLE);
	if (data->win_ptr == NULL)
	{
		free_data(data);
		error_and_exit(MLX_NEW_WINDOW_ERROR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			((t_image *)data->images->content)->ptr, 0, 0);
	mlx_key_hook(data->win_ptr, &key_hooks, data);
	mlx_hook(data->win_ptr, X_DESTROY_NOTIFY, 0, red_cross_hook, data);
	mlx_loop(data->mlx_ptr);
}
