/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:54:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:55:42 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_intersection	closest_intersection(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[2/*NB_OBJ*/] = {i_sphere, i_plane/*,
		i_square, i_cylinder, i_triangle*/}; //i_ -> intersect_
	double			cur_t;
	t_list			*closest_elem;
	double			closest_t;

	closest_t = t_max;
	closest_elem = NULL;
	while (obj != NULL)
	{
		cur_t = find_t[((t_obj *)obj->content)->type](&ray, ((t_obj *)obj->content)->obj);
		if (cur_t >= t_min && cur_t < closest_t) // ou >= 1? ; et s'il y a deux memes t
		{
			closest_t = cur_t;
			closest_elem = obj;
		}
		obj = obj->next;
	}
	return ((t_intersection){closest_elem, closest_t});
}

t_bool	intersection_or_not(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[2/*NB_OBJ*/] = {i_sphere, i_plane/*,
		i_square, i_cylinder, i_triangle*/};
	double			cur_t;

	while (obj != NULL)
	{
		cur_t = find_t[((t_obj *)obj->content)->type](&ray, ((t_obj *)obj->content)->obj);
		if (cur_t >= t_min && cur_t < t_max) // ou >= 1? ; et s'il y a deux memes t
			return (TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

t_bool	shadows(t_point cur_pos, t_vector light_dir, t_list *objects)
{
	t_ray	light_ray;

	light_ray.origin = cur_pos;
	light_ray.direction = light_dir;
	if (intersection_or_not(light_ray, objects, 0.00001 /**/, 1) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

double	lighting(t_point cur_pos, t_list *elem, t_global *data)
{
	static t_normal	calc_normal[2/*NB_OBJ*/] = {n_sphere, n_plane/*,
		n_square, n_cylinder, n_triangle*/}; //n_ -> normal_
	t_vector		normal;
	double			intensity;
	t_light			*cur_light; // faire pareil pour les deux fonctions d'intersection?
	t_list			*lights_iter;
	t_vector		light_dir;
	double			n_dot_l;

	normal = calc_normal[((t_obj *)elem->content)->type](cur_pos, ((t_obj *)elem->content)->obj);
	intensity = 0.0;
	lights_iter = data->lights;
	while (lights_iter != NULL)
	{
		cur_light = ((t_light *)lights_iter->content);
		light_dir = sub(cur_light->position, cur_pos);
		n_dot_l = dot(normal, light_dir);
		if (n_dot_l > 0)
		{
			if (shadows(cur_pos, light_dir, data->objects) == FALSE)
			{
				n_dot_l /= length(normal) * length(light_dir);
				intensity += cur_light->intensity * n_dot_l;// div by zero
			}
		}
		lights_iter = lights_iter->next;
	}
	//printf("intensity %f\n", intensity);
	return (intensity);
}

int		rgb_fit_to_range(int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (value);
}

int		rgb_to_int(t_rgb color)
{
	int		ret;
	double	tmp;

	tmp = round(color.x);
	ret = rgb_fit_to_range((int)tmp);
	tmp = round(color.y);
	ret = (ret << 8) | rgb_fit_to_range((int)tmp);
	tmp = round(color.z);
	ret = (ret << 8) | rgb_fit_to_range((int)tmp);
	return (ret);
}

int		process_pixel(t_ray ray, t_global *data)// better name? previous: intersection
{
	t_rgb			color;
	t_point			position;
	double			light;
	t_intersection	intxn;

	//ray.direction = unit(ray.direction);
	intxn = closest_intersection(ray, data->objects, 1, 2147483647); // 1 pose pb pour le plan ; define ces constantes
	//printf("t = %f\n", intxn.t);
	if (intxn.t == 2147483647)
		color = (t_rgb){0.0, 0.0, 0.0}; // ou blanc?
	else
	{
		color = ((t_obj *)intxn.obj->content)->color;
		position = add(ray.origin, mult(ray.direction, intxn.t));
		light = lighting(position, intxn.obj, data);
		color = mult(color, light + data->amb_light);
	}
	return (rgb_to_int(color));
}

void	get_view_properties(t_global *data, t_view_properties *props, t_camera *cur_camera)
{
	props->half_height = cur_camera->half_width *
		((double)data->res[1] / (double)data->res[0]);
	props->half_pixel_width = cur_camera->half_width / (double)data->res[0];
	props->x_factor = -1;
	props->x_factor_i = 2 / (double)data->res[0];
	props->x_factor_vec = mult(cur_camera->right_vec,
			props->x_factor * cur_camera->half_width + props->half_pixel_width);
	props->y_factor = 1;
	props->y_factor_i = 2 / (double)data->res[1];
	props->y_factor_vec = mult(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
}

void	next_pixel_x(t_camera *cur_camera, t_view_properties *props)
{
	props->x_factor += props->x_factor_i;
	props->x_factor_vec = mult(cur_camera->right_vec,
		props->x_factor * cur_camera->half_width + props->half_pixel_width);
}

void	next_row_y(t_camera *cur_camera, t_view_properties *props)
{
	props->y_factor -= props->y_factor_i;
	props->y_factor_vec = mult(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
	props->x_factor = -1;
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
	while (y < data->res[1])
	{
		x = 0;
		while (x < data->res[0])
		{
			ray.direction = add(cur_camera->forward_vec,
						add(props.x_factor_vec, props.y_factor_vec));
			if (x == 0 && y == 0)
			{
				printf("ray.dir (x = %4zu, y = %4zu) = ", x, y);
				print_vec(ray.direction);
			}
			color = process_pixel(ray, data);
			pixel_put_converted_color(data, cur_image, (size_t[2]){x, y}, color);
			next_pixel_x(cur_camera, &props);
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
	printf("ray.dir (x = %4zu, y = %4zu) = ", x - 1, y - 1);
	print_vec(ray.direction);
	printf("\n");
}

void	fill_bmp_data(t_global *data, char *file_data, size_t line_padding)
{
	size_t				x;
	size_t				y;
	int					color;
	t_ray				ray;
	t_view_properties	props;
	t_camera			*cur_camera;
	size_t				i;
	char				*data_addr;

	cur_camera = (t_camera *)data->cameras->content;
	get_view_properties(data, &props, cur_camera);
	ray.origin = cur_camera->origin;
	i = BMP_METADATA_SIZE;
	data_addr = file_data + i;
	y = 0;
	while (y < data->res[1])
	{
		i = (data->res[1] - y - 1) * (data->res[0] * 3 + line_padding);
		x = 0;
		while (x < data->res[0])
		{
			ray.direction = add(cur_camera->forward_vec,
						add(props.x_factor_vec, props.y_factor_vec));
			color = process_pixel(ray, data);
			data_addr[i] = color;
			data_addr[i + 1] = color >> 8;
			data_addr[i + 2] = color >> 16;
			next_pixel_x(cur_camera, &props);
			i += 3;
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
}
