#include "parsing.h"

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
	line = parse_unit_vector(line, &(cur_plane->normal));
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
	line = parse_unit_vector(line, &(cur_square->normal));
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
	line = parse_unit_vector(line, &(cur_cylinder->normal));
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
