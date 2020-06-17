/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:00:45 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:57:03 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>
#include <errno.h>

void	image_pixel_put(t_image *image, size_t x, size_t y, unsigned color)
{
	char		*pixel_pos;

	pixel_pos = image->addr + ((int)y * image->line_len +
			(int)x * (image->bits_per_pixel / 8));
	if (image->endian == 0)//LITTLE_ENDIAN
	{
		*pixel_pos = (char)color;
		if (image->bits_per_pixel >= 16)
			*(pixel_pos + 1) = (char)(color >> 8);
		if (image->bits_per_pixel >= 24)
			*(pixel_pos + 2) = (char)(color >> 16);
		if (image->bits_per_pixel >= 32)
			*(pixel_pos + 3) = (char)(color >> 24);
	}
	else if (image->endian == 1) //BIG_ENDIAN
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
}

void	pixel_put_converted_color(t_global *data, t_image *image, size_t px_coord[2], int color)
{
	unsigned	converted_color;

	converted_color = (unsigned)mlx_get_color_value(data->mlx_ptr, color);
	image_pixel_put(image, px_coord[0], px_coord[1], converted_color);
}

void	switch_camera(t_global *data, int8_t order)
{
	static t_image	*cur_image = NULL;
	t_image			*next_image;
	t_list			*images_iter;

	images_iter = data->images;
	if (cur_image == NULL)
		cur_image = ((t_image *)images_iter->content);
	next_image = cur_image;
	while (images_iter != NULL && images_iter->next != NULL)
	{
		if (order == 1 && ((t_image *)images_iter->content) == cur_image)
		{
			next_image = ((t_image *)images_iter->next->content);
			break ;
		}
		else if (order == -1 && ((t_image *)images_iter->next->content) == cur_image)
		{
			next_image = ((t_image *)images_iter->content);
			break ;
		}
		images_iter = images_iter->next;
	}
	if (next_image != cur_image)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, next_image->ptr, 0, 0);
		cur_image = next_image;
	}
}

void	quit_program(t_global *data)
{
	t_list			*images_iter;

	images_iter = data->images;
	while (images_iter != NULL)
	{
		mlx_destroy_image(data->mlx_ptr, ((t_image *)images_iter->content)->ptr);// err?
		images_iter = images_iter->next;
	}
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_data(data);
	exit(EXIT_SUCCESS);
}

t_image	*new_image(t_global *data)
{
	t_image	*new_image;

	errno = 0;
	new_image = (t_image *)malloc(sizeof(t_image));
	if (new_image == NULL)
		return (NULL);// error
	errno = 0;
	if (add_to_list(new_image, &(data->images)) == FAILURE)
		return (NULL);// error
	new_image->ptr = mlx_new_image(data->mlx_ptr, data->res[0], data->res[1]);
	if (new_image->ptr == NULL)
	{
		free_data(data);
		error(MLX_NEW_IMAGE_ERROR);// free mlx_init
	}
	new_image->addr = mlx_get_data_addr(new_image->ptr,
		&(new_image->bits_per_pixel), &(new_image->line_len), &(new_image->endian));
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
		fill_image(data, cur_image, ((t_camera *)cameras_iter->content));
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
		error(MLX_INIT_ERROR);
	}
	check_resolution(data);
	draw_images(data);
	errno = 0;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->res[0], data->res[1], "miniRT");
	if (data->win_ptr == NULL)
	{
		free_data(data);
		error(MLX_NEW_WINDOW_ERROR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			((t_image *)data->images->content)->ptr, 0, 0);
	mlx_key_hook(data->win_ptr, &key_hooks, data);
	mlx_loop(data->mlx_ptr);
}
