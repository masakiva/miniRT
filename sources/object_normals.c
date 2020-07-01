/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:11 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:39:13 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_vector	normal_sphere(t_point position_on_the_surface, void *obj)
{
	t_sphere	*sphere;
	t_vector	normal;

	sphere = (t_sphere *)obj;
	normal = sub_vec(position_on_the_surface, sphere->centre);
	if (sphere->surface_side == INSIDE)
		normal = neg_vec(normal);
	normal = unit_vec(normal, length_vec(normal));
	return (normal);
}

t_vector	normal_plane(t_point position, void *obj)
{
	t_plane		*plane;

	(void)position;
	plane = (t_plane *)obj;
	return (plane->normal);
}

t_vector	normal_triangle(t_point position, void *obj)
{
	t_triangle	*triangle;

	(void)position;
	triangle = (t_triangle *)obj;
	return (triangle->plane.normal);
}

t_vector	normal_square(t_point position, void *obj)
{
	t_square	*square;

	(void)position;
	square = (t_square *)obj;
	return (square->triangle1.plane.normal);
}

t_vector	normal_cylinder(t_point position, void *obj)
{
	t_cylinder	*cylinder;
	t_vector	normal;
	t_point		position_on_the_axis;

	(void)position;
	cylinder = (t_cylinder *)obj;
	position_on_the_axis = mult_vec_f(cylinder->axis_direction,
			cylinder->distance_on_the_axis);
	normal = sub_vec(cylinder->axismiddle_intersectionpoint,
			position_on_the_axis);
	if (cylinder->surface_side == INSIDE)
		normal = neg_vec(normal);
	normal = unit_vec(normal, length_vec(normal));
	return (normal);
}
