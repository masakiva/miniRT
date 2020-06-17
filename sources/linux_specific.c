/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_specific.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:02:11 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 15:34:35 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <mlx.h>
#include <errno.h>

int		key_hooks(int keycode, t_global *data)
{
	if (keycode == KEYCODE_ESCAPE)
		quit_program(data);
	else if (keycode == KEYCODE_RIGHT_ARROW)
		switch_camera(data, 1);
	else if (keycode == KEYCODE_LEFT_ARROW)
		switch_camera(data, -1);
	else
		printf("keycode = %d\n", keycode);
	return (SUCCESS);
}

void	check_resolution(t_global *data)
{
	int		screen_width;
	int		screen_height;

	errno = 0;
	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	if (screen_width <= 0 || screen_height <= 0)
		error_and_exit(MLX_SCREEN_SIZE_ERROR);
	if (data->res[0] == 0 || data->res[0] > (size_t)screen_width)
		data->res[0] = (size_t)screen_width;
	if (data->res[1] == 0 || data->res[1] > (size_t)screen_height)
		data->res[1] = (size_t)screen_height;
}
