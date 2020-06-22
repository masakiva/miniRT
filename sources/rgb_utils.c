/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:40:37 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:40:38 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"
#include <math.h>

t_rgb	apply_gamma_correction(t_rgb color)
{
	color.x = pow(color.x, GAMMA);
	color.y = pow(color.y, GAMMA);
	color.z = pow(color.z, GAMMA);
	//color.x = sqrt(color.x);
	//color.y = sqrt(color.y);
	//color.z = sqrt(color.z);
	return (color);
}

void	majorize_color_channels(t_rgb *color)
{
	if (color->x > 1)
		color->x = 1;
	if (color->y > 1)
		color->y = 1;
	if (color->z > 1)
		color->z = 1;
}

int		rgb_to_int(t_rgb color)
{
	majorize_color_channels(&color);
	return ((int)round(color.x * 255) << 16
			| (int)round(color.y * 255) << 8
			| (int)round(color.z * 255));
}

