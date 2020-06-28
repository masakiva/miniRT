/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_res_cameras_lights.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:40:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 11:49:03 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

const char	*p_resolution(const char *line, t_global *data)
{
	int8_t	i;
	int		tmp;

	if (data->res[WIDTH] > 0 && data->res[HEIGHT] > 0)
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

const char	*p_ambient_lighting(const char *line, t_global *data)
{
	static t_bool	passed_once = 0;
	double			intensity;
	t_rgb			color;

	if (passed_once == 1)
		return (NULL);
	passed_once = 1;
	line = parse_float(line, &intensity);
	if (line == NULL || intensity < 0.0 || intensity > 1.0)
		return (NULL);
	line = parse_color(line, &color);
	if (line == NULL)
		return (NULL);
	data->ambient_light_color = mult_vec_f(color, intensity);
	return (line);
}

const char	*parse_camera_direction(const char *line, t_camera *cur_camera)
{
	double	dir_length;

	line = skip_spaces_tabs(line);
	if (ft_memcmp(line, "at", 2) == 0)
	{
		line = skip_spaces_tabs(line + 2);
		line = parse_coord(line, &(cur_camera->direction));
		cur_camera->direction = sub_vec(cur_camera->direction,
				cur_camera->origin);
		dir_length = length_vec(cur_camera->direction);
		if (line == NULL || dir_length <= 0.0 || (cur_camera->direction.x == 0.0 &&
					cur_camera->direction.z == 0.0))
			return (NULL);
		else
			cur_camera->direction = unit_vec(cur_camera->direction, dir_length);
	}
	else
	{
		line = parse_unit_vector(line, &(cur_camera->direction));
		if (line == NULL || (cur_camera->direction.x == 0.0 &&
					cur_camera->direction.z == 0.0))
			return (NULL);
	}
	return (line);
}

const char	*p_camera(const char *line, t_global *data)
{
	t_camera	*cur_camera;

	errno = 0;
	cur_camera = (t_camera *)malloc(sizeof(t_camera));
	if (cur_camera == NULL)
		return (NULL);
	if (add_to_list((void *)cur_camera, &(data->cameras)) == FAILURE)
		return (NULL);
	line = parse_coord(line, &(cur_camera->origin));
	if (line == NULL)
		return (NULL);
	line = parse_camera_direction(line, cur_camera);
	if (line == NULL)
		return (NULL);
	line = parse_int(line, &(cur_camera->fov));
	if (line == NULL || cur_camera->fov < 0 || cur_camera->fov > 180)
		return (NULL);
	return (line);
}

const char	*p_light(const char *line, t_global *data)
{
	t_light		*cur_light;
	double		intensity;
	t_rgb		color;

	errno = 0;
	cur_light = (t_light *)malloc(sizeof(t_light));
	if (cur_light == NULL)
		return (NULL);
	if (add_to_list((void *)cur_light, &(data->lights)) == FAILURE)
		return (NULL);
	line = parse_coord(line, &(cur_light->position));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &intensity);
	if (line == NULL || intensity < 0.0 || intensity > 1.0)
		return (NULL);
	line = parse_color(line, &color);
	if (line == NULL)
		return (NULL);
	cur_light->color = mult_vec_f(color, intensity);
	return (line);
}
