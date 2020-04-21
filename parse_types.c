/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:40:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/02 16:38:43 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	p_resolution(char *line, t_global *data)
{
	int8_t	i;
	int		tmp;

	i = 0;
	while (i < 2)
	{
		tmp = ft_atoi(line);
		if (tmp >= 0) // ou >
			data->res[i] = (size_t)tmp;
		else
			printf("Resolution must be defined using two positive integers.\n");
		line = skip_int(line);
		i++;
	}
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("Resolution must be defined using two positive integers.\n");
}

void	p_ambient_lightning(char *line, t_global *data)
{
	data->amb_light = ft_atof(line);
	line = skip_float(line);
	if (data->amb_light < 0 || data->amb_light > 1)
		printf("AMBIENT LIGHTNING RATIO NOT IN RANGE [0.0,1.0]\n");

	line = parse_color(line, data->color);
	if (line == NULL)
		printf("COLOR ERROR in lightning");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("AMBIENT LIGHTNING NOT VALID\n");
}

void	p_camera(char *line, t_global *data)
{
	t_camera	*cur_camera;

	cur_camera = (t_camera *)malloc(sizeof(t_camera));

	line = parse_vector(line, &(cur_camera->origin));
	if (line == NULL)
		printf("COORD ERROR\n");

	line = parse_vector(line, &(cur_camera->direction));
	if (line == NULL)
		printf("o_vec ERROR\n");

	cur_camera->fov = ft_atoi(line);
	if (cur_camera->fov < 0 || cur_camera->fov > 180)
		printf("FOV NOT IN RANGE [0,180]\n");
	line = skip_int(line);

	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("CAMERA PARAMETERS NOT VALID\n");
	add_to_list((void *)cur_camera, &(data->cameras));
}

void	p_light(char *line, t_global *data)
{
	t_light		*cur_light;

	cur_light = (t_light *)malloc(sizeof(t_light));
	line = parse_coord(line, cur_light->coord);
	if (line == NULL)
		printf("COORD ERROR");
	cur_light->brightness = ft_atof(line);
	line = skip_float(line);
	if (cur_light->brightness < 0 || cur_light->brightness > 1)
		printf("AMBIENT LIGHTNING RATIO NOT IN RANGE [0.0,1.0]\n");
	line = parse_color(line, cur_light->color);
	if (line == NULL)
		printf("COLOR ERROR");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("CAMERA PARAMETERS NOT VALID\n");
	add_to_list((void *)cur_light, &(data->lights));
}

void	p_sphere(char *line, t_global *data)
{
	t_sphere	*cur_sphere;

	cur_sphere = (t_sphere *)malloc(sizeof(t_sphere));

	line = parse_vector(line, &(cur_sphere->centre));
	if (line == NULL)
		printf("COORD ERROR");

	cur_sphere->radius = ft_atof(line) / 2;
	if (cur_sphere->radius < 0)
		printf("MUST BE POSITIVE");
	line = skip_float(line);

	line = parse_color(line, cur_sphere->color);
	if (line == NULL)
		printf("COLOR ERROR");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("spHERE PARAMETERS NOT VALID\n");
	wrap_object((void *)cur_sphere, &(data->objects), SPHERE);
}

void	p_plane(char *line, t_global *data)
{
	t_plane		*cur_plane;

	cur_plane = (t_plane *)malloc(sizeof(t_plane));

	line = parse_vector(line, &(cur_plane->position));
	if (line == NULL)
		printf("COORD ERROR");

	line = parse_vector(line, &(cur_plane->normal));
	if (line == NULL)
		printf("o_vec ERROR\n");

	line = parse_color(line, cur_plane->color);
	if (line == NULL)
		printf("COLOR ERROR");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("spHERE PARAMETERS NOT VALID\n");
	wrap_object((void *)cur_plane, &(data->objects), PLANE);
}

void	p_square(char *line, t_global *data)
{
	t_square	*cur_square;

	cur_square = (t_square *)malloc(sizeof(t_square));
	line = parse_coord(line, cur_square->coord);
	if (line == NULL)
		printf("COORD ERROR");
	line = parse_o_vec(line, cur_square->o_vec);
	if (line == NULL)
		printf("o_vec ERROR\n");
	cur_square->height = ft_atof(line);
	line = skip_float(line);
	if (cur_square->height < 0)
		printf("MUST BE POSITIVE");
	line = parse_color(line, cur_square->color);
	if (line == NULL)
		printf("COLOR ERROR");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("sQu PARAMETERS NOT VALID\n");
	wrap_object((void *)cur_square, &(data->objects), SQUARE);
}

void	p_cylinder(char *line, t_global *data)
{
	t_cylinder	*cur_cylinder;

	cur_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	line = parse_coord(line, cur_cylinder->coord);
	if (line == NULL)
		printf("COORD ERROR");
	line = parse_o_vec(line, cur_cylinder->o_vec);
	if (line == NULL)
		printf("o_vec ERROR\n");
	cur_cylinder->diameter = ft_atof(line);
	line = skip_float(line);
	if (cur_cylinder->diameter < 0)
		printf("MUST BE POSITIVE");
	cur_cylinder->height = ft_atof(line);
	line = skip_float(line);
	if (cur_cylinder->height < 0)
		printf("MUST BE POSITIVE");
	line = parse_color(line, cur_cylinder->color);
	if (line == NULL)
		printf("COLOR ERROR");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("CYLI PARAMETERS NOT VALID\n");
	wrap_object((void *)cur_cylinder, &(data->objects), CYLINDER);
}

void	p_triangle(char *line, t_global *data)
{
	t_triangle	*cur_triangle;

	cur_triangle = (t_triangle *)malloc(sizeof(t_triangle));
	line = parse_coord(line, cur_triangle->coord1);
	if (line == NULL)
		printf("COORD ERROR");
	line = parse_coord(line, cur_triangle->coord2);
	if (line == NULL)
		printf("COORD ERROR");
	line = parse_coord(line, cur_triangle->coord3);
	if (line == NULL)
		printf("COORD ERROR");
	line = parse_color(line, cur_triangle->color);
	if (line == NULL)
		printf("COLOR ERROR");
	line = skip_sp_ht(line);
	if (*line != '\0')
		printf("TRIAngle PARAMETERS NOT VALID\n");
	wrap_object((void *)cur_triangle, &(data->objects), TRIANGLE);
}
