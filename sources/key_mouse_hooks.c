/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:03 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:39:05 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_handling.h"

t_image	*get_next_image(t_list *images_iter, t_image *cur_image, int8_t order)
{
	if (order == NEXT && ((t_image *)images_iter->content) == cur_image)
		return ((t_image *)images_iter->next->content);
	else if (order == PREVIOUS &&
			((t_image *)images_iter->next->content) == cur_image)
		return ((t_image *)images_iter->content);
	return (cur_image);
}

void	switch_camera(t_global *data, int8_t order)
{
	static t_image	*cur_image = NULL;
	t_image			*next_image;
	t_list			*images_iter;

	images_iter = data->images;
	if (cur_image == NULL)
		cur_image = ((t_image *)images_iter->content);
	while (images_iter != NULL && images_iter->next != NULL)
	{
		next_image = get_next_image(images_iter, cur_image, order);
		if (next_image != cur_image)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, next_image->ptr, 0, 0);
			cur_image = next_image;
			break ;
		}
		images_iter = images_iter->next;
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

int		key_hooks(int keycode, t_global *data)
{
	if (keycode == KEYCODE_ESCAPE)
		quit_program(data);
	else if (keycode == KEYCODE_RIGHT_ARROW)
		switch_camera(data, NEXT);
	else if (keycode == KEYCODE_LEFT_ARROW)
		switch_camera(data, PREVIOUS);
	else
		printf("keycode = %d\n", keycode);
	return (SUCCESS);
}

int		red_cross_hook(t_global *data)
{
	quit_program(data);
	return (SUCCESS);
}
