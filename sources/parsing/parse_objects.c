/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:41:30 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:41:41 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

const char	*p_sphere(const char *line, t_global *data)
{
	t_sphere	*sphere;
	t_rgb		*color_ptr;

	errno = 0;
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)sphere, &(data->objects), SPHERE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(sphere->centre));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &(sphere->radius));
	if (line == NULL || sphere->radius < 0.0)
		return (NULL);
	sphere->radius /= 2.0;
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_plane(const char *line, t_global *data)
{
	t_plane		*plane;
	t_rgb		*color_ptr;

	errno = 0;
	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)plane, &(data->objects), PLANE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(plane->position));
	if (line == NULL)
		return (NULL);
	line = parse_unit_vector(line, &(plane->normal));
	if (line == NULL)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_triangle(const char *line, t_global *data)
{
	t_triangle	*triangle;
	t_rgb		*color_ptr;

	errno = 0;
	triangle = (t_triangle *)malloc(sizeof(t_triangle));
	if (triangle == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)triangle, &(data->objects), TRIANGLE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(triangle->vertex1));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(triangle->vertex2));
	if (line == NULL)
		return (NULL);
	line = parse_coord(line, &(triangle->vertex3));
	if (line == NULL)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_square(const char *line, t_global *data)
{
	t_square	*square;
	t_rgb		*color_ptr;

	errno = 0;
	square = (t_square *)malloc(sizeof(t_square));
	if (square == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)square, &(data->objects), SQUARE);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(square->centre));
	if (line == NULL)
		return (NULL);
	line = parse_unit_vector(line, &(square->normal));
	if (line == NULL || (square->normal.x == 0.0 &&
				square->normal.z == 0.0))
		return (NULL);
	line = parse_float(line, &(square->side_len));
	if (line == NULL || square->side_len < 0.0)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}

const char	*p_cylinder(const char *line, t_global *data)
{
	t_cylinder	*cylinder;
	t_rgb		*color_ptr;

	errno = 0;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (NULL);
	color_ptr = wrap_object((void *)cylinder, &(data->objects), CYLINDER);
	if (color_ptr == NULL)
		return (NULL);
	line = parse_coord(line, &(cylinder->axis_middle));
	if (line == NULL)
		return (NULL);
	line = parse_unit_vector(line, &(cylinder->axis_direction));
	if (line == NULL)
		return (NULL);
	line = parse_float(line, &(cylinder->radius));
	if (line == NULL || cylinder->radius < 0.0)
		return (NULL);
	cylinder->radius /= 2.0;
	line = parse_float(line, &(cylinder->height));
	if (line == NULL || cylinder->height < 0.0)
		return (NULL);
	line = parse_color(line, color_ptr);
	return (line);
}
