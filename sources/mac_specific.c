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

#include "mlx_handling.h"

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
