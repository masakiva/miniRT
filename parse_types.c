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

#include "minirt.h"
#include <stdlib.h>

char	*p_resolution(char *line, t_global *data)
{
	int8_t	i;
	int		tmp;

	i = 0;
	while (i < 2)
	{
		tmp = ft_atoi(line);
		if (tmp >= 0) // 0 included?
		{
			data->res[i] = (size_t)tmp;
			line = skip_int(line);
			i++;
		}
		else
		{
			line = NULL;
			break ;
		}
	}
	return (line);
}

char	*p_ambient_lightning(char *line, t_global *data)
{
	line = parse_float(line, &(data->amb_light));
	if (line != NULL && data->amb_light >= 0.0 && data->amb_light <= 1.0)
	{
		line = parse_color(line, &(data->color));
		//errr
	}
	else // hmm
		line = NULL;
	return (line);
}

char	*p_camera(char *line, t_global *data)
{
	t_camera	*cur_camera;

	cur_camera = (t_camera *)malloc(sizeof(t_camera));
	line = parse_vector(line, &(cur_camera->origin));
	if (line != NULL)
	{
		line = parse_vector(line, &(cur_camera->direction));
		if (line != NULL)
		{
			line = parse_int(line, &(cur_camera->fov));
			if (cur_camera->fov >= 0 && cur_camera->fov <= 180)
			{
				add_to_list((void *)cur_camera, &(data->cameras));
			}
		}
	}
	return (line);
}

char	*p_light(char *line, t_global *data) // error in return, ptr of line in parameter
{
	t_light		*cur_light;

	cur_light = (t_light *)malloc(sizeof(t_light));
	line = parse_vector(line, &(cur_light->position));
	if (line == NULL)
		printf("coord error");
	cur_light->brightness = ft_atof(line);
	line = skip_float(line);
	if (cur_light->brightness < 0.0 || cur_light->brightness > 1.0)
		printf("ambient lightning ratio not in range [0.0,1.0]\n");
	line = parse_color(line, &(cur_light->color));
	if (line == NULL)
		printf("color error");
	add_to_list((void *)cur_light, &(data->lights));
	return (line);
}

char	*p_sphere(char *line, t_global *data)
{
	t_sphere	*cur_sphere;

	//errno = 0; // for malloc
	cur_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (cur_sphere == NULL) return (NULL);
	line = parse_vector(line, &(cur_sphere->centre));
	if (line == NULL) return (NULL);
	line = parse_float(line, &(cur_sphere->radius));
	if (cur_sphere->radius < 0) return (NULL);
	cur_sphere->radius /= 2;
	if (line == NULL) return (NULL); //errrrrrrr
	line = wrap_object((void *)cur_sphere, &(data->objects), SPHERE, line);
	return (line);
}

char	*p_plane(char *line, t_global *data)
{
	t_plane		*cur_plane;

	cur_plane = (t_plane *)malloc(sizeof(t_plane));

	line = parse_vector(line, &(cur_plane->position));
	line = parse_vector(line, &(cur_plane->normal));
	line = wrap_object((void *)cur_plane, &(data->objects), PLANE, line);
	return (line);
}

char	*p_square(char *line, t_global *data)
{
	t_square	*cur_square;

	cur_square = (t_square *)malloc(sizeof(t_square));
	line = parse_coord(line, cur_square->coord);
	line = parse_o_vec(line, cur_square->o_vec);
	cur_square->height = ft_atof(line);
	line = skip_float(line);
	if (cur_square->height < 0)
		printf("MUST BE POSITIVE");
	line = wrap_object((void *)cur_square, &(data->objects), SQUARE, line);
	return (line);
}

char	*p_cylinder(char *line, t_global *data)
{
	t_cylinder	*cur_cylinder;

	cur_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	line = parse_coord(line, cur_cylinder->coord);
	line = parse_o_vec(line, cur_cylinder->o_vec);
	cur_cylinder->diameter = ft_atof(line);
	line = skip_float(line);
	if (cur_cylinder->diameter < 0)
		printf("MUST BE POSITIVE");
	cur_cylinder->height = ft_atof(line);
	line = skip_float(line);
	if (cur_cylinder->height < 0)
		printf("MUST BE POSITIVE");
	line = wrap_object((void *)cur_cylinder, &(data->objects), CYLINDER, line);
	return (line);
}

char	*p_triangle(char *line, t_global *data)
{
	t_triangle	*cur_triangle;

	cur_triangle = (t_triangle *)malloc(sizeof(t_triangle));
	line = parse_coord(line, cur_triangle->coord1);
	line = parse_coord(line, cur_triangle->coord2);
	line = parse_coord(line, cur_triangle->coord3);
	line = wrap_object((void *)cur_triangle, &(data->objects), TRIANGLE, line);
	return (line);
}
