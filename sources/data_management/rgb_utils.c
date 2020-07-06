/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:40:37 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:18:49 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_management.h"

static void	majorize_color_channels(t_rgb *color)
{
	if (color->x > 1.0)
		color->x = 1.0;
	if (color->y > 1.0)
		color->y = 1.0;
	if (color->z > 1.0)
		color->z = 1.0;
}

int			rgb_to_int(t_rgb color)
{
	majorize_color_channels(&color);
	return ((int)lround(color.x * 255.0) << 16
			| (int)lround(color.y * 255.0) << 8
			| (int)lround(color.z * 255.0));
}
