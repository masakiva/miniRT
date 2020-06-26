/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:40:37 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 14:22:45 by mvidal-a         ###   ########.fr       */
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
	if (color->x > 1.0)
		color->x = 1.0;
	if (color->y > 1.0)
		color->y = 1.0;
	if (color->z > 1.0)
		color->z = 1.0;
}

int		rgb_to_int(t_rgb color)
{
	majorize_color_channels(&color);
	return ((int)lround(color.x * 255.0) << 16
			| (int)lround(color.y * 255.0) << 8
			| (int)lround(color.z * 255.0));
}
