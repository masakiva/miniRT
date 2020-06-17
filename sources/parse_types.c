/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:40:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/02 16:38:43 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>
#include <errno.h>
#include <math.h>

const char	*p_resolution(const char *line, t_global *data)
{
	int8_t	i;
	int		tmp;

	if (data->res[0] > 0 && data->res[1] > 0)
		return (NULL);
	i = 0;
	while (i < 2)
	{
		line = parse_int(line, &tmp);
		if (line == NULL || tmp <= 0)
			return (NULL);
		data->res[i] = (size_t)tmp;
		i++;
	}
	return (line);
}

const char	*p_ambient_lightning(const char *line, t_global *data)
{
	static t_bool	passed_once = 0;

	if (passed_once == 1)
		return (NULL);
	passed_once = 1;
	line = parse_float(line, &(data->amb_light));
	if (line == NULL || data->amb_light < 0.0 || data->amb_light > 1.0)
		return (NULL);
	line = parse_color(line, &(data->color));
	return (line);
}

void		calc_camera_properties(t_camera *cur_camera, t_point target, int fov)
{
	cur_camera->forward_vec = unit(sub(target, cur_camera->origin));
	if (cur_camera->forward_vec == NULL)
		return (NULL);
	cur_camera->right_vec = unit(cross(cur_camera->forward_vec,
				(t_vector){0.0, 1.0, 0.0}));
	cur_camera->up_vec = cross(cur_camera->right_vec, cur_camera->forward_vec);
	cur_camera->half_width = tan((M_PI * fov / 180) / 2);
}

const char	*p_camera(const char *line, t_global *data)
{
	t_camera	*cur_camera;
	t_point		target;
	int			fov;

	errno = 0;
	cur_camera = (t_camera *)malloc(sizeof(t_camera));
	if (cur_camera == NULL)
		return (NULL);
	if (add_to_list((void *)cur_camera, &(data->cameras)) == FAILURE)
		return (NULL);
	line = parse_coord(line, &(cur_camera->origin));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &target);
	if (line == NULL)
		return (NULL);
	line = parse_int(line, &fov);
	if (line == NULL || fov < 0 || fov > 180)
		return (NULL);
	calc_camera_properties(cur_camera, target, fov);
	return (line);
}

const char	*p_light(const char *line, t_global *data)
{
	t_light		*cur_light;

	errno = 0;
	cur_light = (t_light *)malloc(sizeof(t_light));
	if (cur_light == NULL)
		return (NULL);
	if (add_to_list((void *)cur_light, &(data->lights)) == FAILURE)
		return (NULL);
	line = parse_coord(line, &(cur_light->position));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &(cur_light->intensity));
	if (line == NULL || cur_light->intensity < 0.0 || cur_light->intensity > 1.0)
		return (NULL);
	line = parse_color(line, &(cur_light->color));
	return (line);
}

const char	*p_sphere(const char *line, t_global *data)
{
	t_sphere	*cur_sphere;
	t_rgb		*color_ptr;

	errno = 0;
	cur_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (cur_sphere == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)cur_sphere, &(data->objects), SPHERE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_sphere->centre));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &(cur_sphere->radius));
	if (line == NULL || cur_sphere->radius < 0.0)
		return (NULL);
	cur_sphere->radius /= 2.0;
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_plane(const char *line, t_global *data)
{
	t_plane		*cur_plane;
	t_rgb		*color_ptr;

	errno = 0;
	cur_plane = (t_plane *)malloc(sizeof(t_plane));
	if (cur_plane == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)cur_plane, &(data->objects), PLANE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_plane->position));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_plane->normal));
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_square(const char *line, t_global *data)
{
	t_square	*cur_square;
	t_rgb		*color_ptr;

	errno = 0;
	cur_square = (t_square *)malloc(sizeof(t_square));
	if (cur_square == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)cur_square, &(data->objects), SQUARE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_square->position));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_square->normal));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &(cur_square->height));
	if (line == NULL || cur_square->height < 0.0)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_cylinder(const char *line, t_global *data)
{
	t_cylinder	*cur_cylinder;
	t_rgb		*color_ptr;

	errno = 0;
	cur_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cur_cylinder == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)cur_cylinder, &(data->objects), CYLINDER);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_cylinder->position));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_cylinder->normal));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &(cur_cylinder->diameter));
	if (line == NULL || cur_cylinder->diameter < 0.0)
		return (NULL);
	line = parse_float(line, &(cur_cylinder->height));
	if (line == NULL || cur_cylinder->height < 0.0)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_triangle(const char *line, t_global *data)
{
	t_triangle	*cur_triangle;
	t_rgb		*color_ptr;

	errno = 0;
	cur_triangle = (t_triangle *)malloc(sizeof(t_triangle));
	if (cur_triangle == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)cur_triangle, &(data->objects), TRIANGLE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_triangle->vertex1));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_triangle->vertex2));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(cur_triangle->vertex3));
	if (line == NULL)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}
