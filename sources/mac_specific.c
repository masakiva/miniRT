/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_specific.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:00:39 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 15:34:50 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		key_hooks(int keycode, t_global *data)
{
	if (keycode == MACOS_KEYCODE_ESCAPE)
		quit_program(data);
	else if (keycode == MACOS_KEYCODE_RIGHT_ARROW)
		switch_camera(data, 1);
	else if (keycode == MACOS_KEYCODE_LEFT_ARROW)
		switch_camera(data, -1);
	else
		printf("keycode = %d\n", keycode);
	return (SUCCESS);
}

void	check_resolution(t_global *data)
{
	size_t	screen_width;
	size_t	screen_height;

	screen_width = 2560;
	screen_height = 1440;
	if (data->res[0] == 0 || data->res[0] > screen_width)
		data->res[0] = screen_width;
	if (data->res[1] == 0 || data->res[1] > screen_height)
		data->res[1] = screen_height;
}
