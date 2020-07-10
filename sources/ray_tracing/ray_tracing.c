/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:22:23 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/10 23:34:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

static t_intersection	closest_intersection(t_ray ray, t_list *obj_iter)
{
	static t_equations	find_t[NB_OBJ] = {intersect_sphere, intersect_plane,
		intersect_triangle, intersect_square, intersect_cylinder};
	double				cur_t;
	double				closest_t;
	t_obj_wrapper		*cur_obj;
	t_obj_wrapper		*closest_obj;

	closest_t = T_MAX;
	closest_obj = NULL;
	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		cur_t = find_t[cur_obj->type](&ray, cur_obj->obj, 0.0);
		if (cur_t >= EPSILON && cur_t < closest_t)
		{
			closest_t = cur_t;
			closest_obj = cur_obj;
		}
		obj_iter = obj_iter->next;
	}
	return ((t_intersection){closest_obj, closest_t});
}

static int				process_pixel(t_ray ray, t_global *data)
{
	t_rgb			obj_color;
	t_rgb			light_color;
	t_point			position;
	t_intersection	intersection;

	intersection = closest_intersection(ray, data->objects);
	if (intersection.obj_wrapper == NULL)
		obj_color = (t_rgb){0.0, 0.0, 0.0};
	else
	{
		obj_color = intersection.obj_wrapper->color;
		position = add_vec(ray.origin, mult_vec_f(ray.direction,
					intersection.t));
		light_color = (t_rgb){0.0, 0.0, 0.0};
		light_color = lighting(position, intersection.obj_wrapper, data,
				light_color);
		obj_color = mult_vec_vec(obj_color, light_color);
	}
	return (rgb_to_int(obj_color));
}

static void				set_bmp_pixel_color(t_camera *cur_camera,
		t_view_properties *props, t_global *data, char *pixel_pos)
{
	t_ray				ray;
	int					color;

	ray.origin = cur_camera->origin;
	ray.direction = add_vec(cur_camera->direction,
			add_vec(props->x_factor_vec, props->y_factor_vec));
	color = process_pixel(ray, data);
	pixel_put_bmp_little_endian(pixel_pos, color);
}

void					fill_bmp_data(t_global *data, char *data_addr,
		size_t line_padding)
{
	size_t				x;
	size_t				y;
	t_view_properties	props;
	t_camera			*cur_camera;
	size_t				i;

	cur_camera = (t_camera *)data->cameras->content;
	calc_view_properties(data, cur_camera, &props);
	i = BMP_METADATA_SIZE;
	y = 0;
	while (y < data->res[HEIGHT])
	{
		i = (data->res[HEIGHT] - y - 1) * (data->res[WIDTH] * 3 + line_padding);
		x = 0;
		while (x < data->res[WIDTH])
		{
			set_bmp_pixel_color(cur_camera, &props, data, data_addr + i);
			next_pixel_x(&props);
			i += 3;
			x++;
		}
		next_row_y(&props);
		y++;
	}
}

void					fill_mlx_image(t_global *data, t_mlx_image *cur_image,
		t_camera *cur_camera)
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
