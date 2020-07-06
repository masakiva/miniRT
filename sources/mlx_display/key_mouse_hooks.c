/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:03 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:24:03 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_display.h"

int			key_hooks(int keycode, t_global *data)
{
	if (keycode == KEYCODE_ESCAPE)
		quit_program(data);
	else if (keycode == KEYCODE_RIGHT_ARROW)
		switch_camera(data, NEXT_IMAGE);
	else if (keycode == KEYCODE_LEFT_ARROW)
		switch_camera(data, PREVIOUS_IMAGE);
	return (SUCCESS);
}

int			refresh_window(t_global *data)
{
	switch_camera(data, SAME_IMAGE);
	return (SUCCESS);
}

int			red_cross_hook(t_global *data)
{
	quit_program(data);
	return (SUCCESS);
}
