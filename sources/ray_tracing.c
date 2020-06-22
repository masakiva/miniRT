/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:54:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:40:27 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

int		process_pixel(t_ray ray, t_global *data)
{
	t_rgb			color;
//	t_point			position;
	t_intersection	intxn;

	//ray.direction = unit_vec(ray.direction, length_vec(ray.direction));
	intxn = closest_intersection(ray, data->objects, RAY_T_MIN, RAY_T_MAX);
	if (intxn.t == RAY_T_MAX)
		color = (t_rgb){0.0, 0.0, 0.0};
	else
	{
		color = ((t_obj *)intxn.obj->content)->color;
//		position = add_vec(ray.origin, mult_vec_f(ray.direction, intxn.t));
//		color = mult_vec_vec(color, lighting(position, intxn.obj, data));
	}
	//color = apply_gamma_correction(color);
	return (rgb_to_int(color));
}

void	get_view_properties(t_global *data, t_view_properties *props, t_camera *cur_camera)
{
	props->half_height = cur_camera->half_width *
		((double)data->res[HEIGHT] / (double)data->res[WIDTH]);
	props->half_pixel_width = cur_camera->half_width / (double)data->res[WIDTH];
	props->x_factor = -1;
	props->x_factor_i = 2 / (double)data->res[WIDTH];
	props->x_factor_vec = mult_vec_f(cur_camera->right_vec,
			props->x_factor * cur_camera->half_width + props->half_pixel_width);
	props->y_factor = 1;
	props->y_factor_i = 2 / (double)data->res[HEIGHT];
	props->y_factor_vec = mult_vec_f(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
}

void	next_pixel_x(t_camera *cur_camera, t_view_properties *props)
{
	props->x_factor += props->x_factor_i;
	props->x_factor_vec = mult_vec_f(cur_camera->right_vec,
		props->x_factor * cur_camera->half_width + props->half_pixel_width);
}

void	next_row_y(t_camera *cur_camera, t_view_properties *props)
{
	props->y_factor -= props->y_factor_i;
	props->y_factor_vec = mult_vec_f(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
	props->x_factor = -1;
	props->x_factor_vec = mult_vec_f(cur_camera->right_vec,
		props->x_factor * cur_camera->half_width + props->half_pixel_width);
}

void	fill_mlx_image(t_global *data, t_image *cur_image, t_camera *cur_camera)
{
	size_t				x;
	size_t				y;
	int					color;
	t_ray				ray;
	t_view_properties	props;

	get_view_properties(data, &props, cur_camera);
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
			next_pixel_x(cur_camera, &props);
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
}
