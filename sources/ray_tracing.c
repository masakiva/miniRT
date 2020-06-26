/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:54:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 13:54:56 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

int		process_pixel(t_ray ray, t_global *data)
{
	t_rgb			color;
	t_point			position;
	t_intersection	intersection;

	//ray.direction = unit_vec(ray.direction, length_vec(ray.direction));
	intersection = closest_intersection(ray, data->objects, RAY_T_MIN,
			RAY_T_MAX);
	if (intersection.obj_wrapper == NULL) // -> intersection.obj_wrapper == NULL
		color = (t_rgb){0.0, 0.0, 0.0};
	else
	{
		color = intersection.obj_wrapper->color;
		position = add_vec(ray.origin, mult_vec_f(ray.direction,
					intersection.t));
		color = mult_vec_vec(color, lighting(position, intersection.obj_wrapper,
					data));
	}
	//color = apply_gamma_correction(color);
	return (rgb_to_int(color));
}

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

void	fill_mlx_image(t_global *data, t_mlx_image *cur_image, t_camera *cur_camera)
{
	size_t				x;
	size_t				y;
	int					color;
	t_ray				ray;
	t_view_properties	props;

	calc_view_properties(data, cur_camera, &props);
	ray.origin = cur_camera->origin;
	y = 0;
	while (y < data->res[HEIGHT])
	{
		x = 0;
		while (x < data->res[WIDTH])
		{
			ray.direction = add_vec(cur_camera->direction,
						add_vec(props.x_factor_vec, props.y_factor_vec));
			color = process_pixel(ray, data);
			pixel_put_mlx_image(cur_image, x, y,
					convert_color(data->mlx_ptr, color));
			next_pixel_x(&props);
			x++;
		}
		next_row_y(&props);
		y++;
	}
}
