/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:54:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/18 16:18:55 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_intersection	closest_intersection(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[2/*NB_OBJ*/] = {intersect_sphere, intersect_plane/*,
		intersect_square, intersect_cylinder, intersect_triangle*/};
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
	static t_equations	find_t[2/*NB_OBJ*/] = {intersect_sphere, intersect_plane/*,
		intersect_square, intersect_cylinder, intersect_triangle*/};
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
	static t_normal	calc_normal[2/*NB_OBJ*/] = {normal_sphere, normal_plane/*,
		normal_square, normal_cylinder, normal_triangle*/};
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
		light_dir = sub_vec(cur_light->position, cur_pos);
		n_dot_l = dot_vec(normal, light_dir);
		if (n_dot_l > 0)
		{
			if (shadows(cur_pos, light_dir, data->objects) == FALSE)
			{
				n_dot_l /= length_vec(normal) * length_vec(light_dir);
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

int		process_pixel(t_ray ray, t_global *data)
{
	t_rgb			color;
	t_point			position;
	double			light;
	t_intersection	intxn;

	//ray.direction = unit(ray.direction);
	intxn = closest_intersection(ray, data->objects, 1, 2147483647); // 1 pose pb pour le plan ; define ces constantes
	if (intxn.t == 2147483647)
		color = (t_rgb){0.0, 0.0, 0.0};
	else
	{
		color = ((t_obj *)intxn.obj->content)->color;
		position = add_vec(ray.origin, mult_vec(ray.direction, intxn.t));
		light = lighting(position, intxn.obj, data);
		color = mult_vec(color, light + data->amb_light_intensity);
	}
	return (rgb_to_int(color));
}

void	get_view_properties(t_global *data, t_view_properties *props, t_camera *cur_camera)
{
	props->half_height = cur_camera->half_width *
		((double)data->resolution[HEIGHT] / (double)data->resolution[WIDTH]);
	props->half_pixel_width = cur_camera->half_width / (double)data->resolution[WIDTH];
	props->x_factor = -1;
	props->x_factor_i = 2 / (double)data->resolution[WIDTH];
	props->x_factor_vec = mult_vec(cur_camera->right_vec,
			props->x_factor * cur_camera->half_width + props->half_pixel_width);
	props->y_factor = 1;
	props->y_factor_i = 2 / (double)data->resolution[HEIGHT];
	props->y_factor_vec = mult_vec(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
}

void	next_pixel_x(t_camera *cur_camera, t_view_properties *props)
{
	props->x_factor += props->x_factor_i;
	props->x_factor_vec = mult_vec(cur_camera->right_vec,
		props->x_factor * cur_camera->half_width + props->half_pixel_width);
}

void	next_row_y(t_camera *cur_camera, t_view_properties *props)
{
	props->y_factor -= props->y_factor_i;
	props->y_factor_vec = mult_vec(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
	props->x_factor = -1;
}

void	pixel_put_mlx_image(t_image *image, size_t x, size_t y, unsigned color)
{
	char		*pixel_pos;

	pixel_pos = image->addr + ((int)y * image->line_len +
			(int)x * (image->bits_per_pixel / 8));
	if (image->endian == LITTLE_ENDIAN_)
	{
		*pixel_pos = (char)color;
		if (image->bits_per_pixel >= 16)
			*(pixel_pos + 1) = (char)(color >> 8);
		if (image->bits_per_pixel >= 24)
			*(pixel_pos + 2) = (char)(color >> 16);
		if (image->bits_per_pixel >= 32)
			*(pixel_pos + 3) = (char)(color >> 24);
	}
	else if (image->endian == BIG_ENDIAN_)
	{
		if (image->bits_per_pixel >= 32)
		{
			*(pixel_pos + 3) = (char)color;
			*(pixel_pos + 2) = (char)(color >> 8);
			*(pixel_pos + 1) = (char)(color >> 16);
			*pixel_pos = (char)(color >> 24);
		}
		else if (image->bits_per_pixel >= 24)
		{
			*(pixel_pos + 2) = (char)color;
			*(pixel_pos + 1) = (char)(color >> 8);
			*pixel_pos = (char)(color >> 16);
		}
		else if (image->bits_per_pixel >= 16)
		{
			*(pixel_pos + 1) = (char)color;
			*pixel_pos = (char)(color >> 8);
		}
		else if (image->bits_per_pixel >= 8)
			*pixel_pos = (char)color;
	}
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
	while (y < data->resolution[HEIGHT])
	{
		x = 0;
		while (x < data->resolution[WIDTH])
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
	while (y < data->resolution[HEIGHT])
	{
		i = (data->resolution[HEIGHT] - y - 1) * (data->resolution[WIDTH] * 3 + line_padding);
		x = 0;
		while (x < data->resolution[WIDTH])
		{
			ray.direction = add_vec(cur_camera->direction,
						add_vec(props.x_factor_vec, props.y_factor_vec));
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
