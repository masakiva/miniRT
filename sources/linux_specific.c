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

#include "mlx_handling.h"

int		key_hooks(int keycode, t_global *data)
{
	if (keycode == KEYCODE_ESCAPE) // add conditional defines to the header
		quit_program(data);
	else if (keycode == KEYCODE_RIGHT_ARROW)
		switch_camera(data, 1);
	else if (keycode == KEYCODE_LEFT_ARROW)
		switch_camera(data, -1);
	else
		printf("keycode = %d\n", keycode);
	return (SUCCESS);
}
