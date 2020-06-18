/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_res_cameras_lights.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:40:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/18 16:39:48 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

const char	*p_resolution(const char *line, t_global *data)
{
	int8_t	i;
	int		tmp;

	if (data->resolution[WIDTH] > 0 && data->resolution[HEIGHT] > 0)
		return (NULL);
	i = 0;
	while (i < 2)
	{
		line = parse_int(line, &tmp);
		if (line == NULL || tmp <= 0)
			return (NULL);
		data->resolution[i] = (size_t)tmp;
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
	line = parse_float(line, &(data->amb_light_intensity));
	if (line == NULL ||
			data->amb_light_intensity < 0.0 || data->amb_light_intensity > 1.0)
		return (NULL);
	line = parse_color(line, &(data->amb_light_color));
	return (line);
}

static void	calc_camera_properties(t_camera *cur_camera, int fov)
{
	double		dir_vec_length;
	t_vector	upguide;
	double		right_vec_length;

	dir_vec_length = length_vec(cur_camera->direction);
	if (dir_vec_length != 1.0 && dir_vec_length != 0.0) // deuxieme possible??
	{
		cur_camera->direction = unit_vec(cur_camera->direction, dir_vec_length);
		ft_putstr_fd("Warning\nThe camera's direction has been normalized, "\
				"as it wasn't.\n", STDERR_FILENO);
	}
	upguide = (t_vector){0.0, 1.0, 0.0};
	cur_camera->right_vec = cross_vec(upguide, cur_camera->direction);
	right_vec_length = length_vec(cur_camera->right_vec);
	if (right_vec_length == 0.0) // meme pb qu'au dessus
		;//error ; si pas error, peut transferer cette fonction dans l'algo,
			// et ainsi retirer math.h et vectors.h
	cur_camera->right_vec = unit_vec(cur_camera->right_vec, right_vec_length);
	cur_camera->up_vec = cross_vec(cur_camera->direction, cur_camera->right_vec);
	cur_camera->half_width = tan((M_PI * fov / 180) / 2);
}

const char	*p_camera(const char *line, t_global *data)
{
	t_camera	*cur_camera;
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
	line = parse_unit_vector(line, &(cur_camera->direction));
	if (line == NULL)
		return (NULL);
	line = parse_int(line, &fov);
	if (line == NULL || fov < 0 || fov > 180)
		return (NULL);
	calc_camera_properties(cur_camera, fov);
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
