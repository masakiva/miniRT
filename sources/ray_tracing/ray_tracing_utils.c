/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:22:20 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:22:21 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

void	next_pixel_x(t_view_properties *props)
{
	props->x_factor += props->x_factor_i;
	props->x_factor_vec = mult_vec_f(props->right_vec,
		props->x_factor * props->half_width + props->half_pixel_width);
}

void	next_row_y(t_view_properties *props)
{
	props->y_factor -= props->y_factor_i;
	props->y_factor_vec = mult_vec_f(props->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
	props->x_factor = -1.0;
	props->x_factor_vec = mult_vec_f(props->right_vec,
		props->x_factor * props->half_width + props->half_pixel_width);
}
