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
	//  There are two design decisions to make for normals. The first is
	//  whether these normals are unit length. That is convenient for shading
	//  so I will say yes, but I won’t enforce that in the code. This could
	//  allow subtle bugs, so be aware this is personal preference as are most
	//  design decisions like that.
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
	return (triangle->triangle_plane.normal);
}

t_vector	normal_square(t_point position, void *obj)
{
	t_square	*square;

	(void)position;
	square = (t_square *)obj;
	return (square->normal);
}

t_vector	normal_cylinder(t_point position_on_the_surface, void *obj)
{
	t_cylinder	*cylinder;
	t_vector	normal;
	t_vector	rayorigin_middle;
	double		distance_on_the_axis;

	cylinder = (t_cylinder *)obj;
	rayorigin_middle = sub_vec(cylinder->axis_middle, cylinder->camera_origin);
	distance_on_the_axis = dot_vec(cylinder->axis_direction,
			sub_vec(position_on_the_surface, rayorigin_middle));
	normal = sub_vec(sub_vec(position_on_the_surface,
				mult_vec_f(cylinder->axis_direction, distance_on_the_axis)),
				rayorigin_middle);
	if (cylinder->surface_side == INSIDE)
		normal = neg_vec(normal);
	normal = unit_vec(normal, length_vec(normal));// utile?
	return (normal);
}
