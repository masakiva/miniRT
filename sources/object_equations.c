/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_equations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:56:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 14:04:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

double	intersect_sphere(t_ray *ray, void *obj)
{
	t_sphere	*sphere;
	double		a;
	double		half_b;
	double		discriminant;
	double		t;

	sphere = (t_sphere *)obj;
	sphere->centre_rayorigin = sub_vec(ray->origin, sphere->centre);//////
	sphere->c = length_squared_vec(sphere->centre_rayorigin) -
		sq(sphere->radius);//////
	a = length_squared_vec(ray->direction);
	half_b = dot_vec(ray->direction, sphere->centre_rayorigin);
	discriminant = sq(half_b) - a * sphere->c;
	t = RAY_T_MAX;
	if (discriminant >= 0.0)
	{
		if (sphere->surface_side == OUTSIDE)
			t = (-1.0 * half_b - sqrt(discriminant)) / a;// div par zero si ray->dir = 0
		else
			t = (-1.0 * half_b + sqrt(discriminant)) / a;// div par zero si ray->dir = 0
	}
	return (t);
	// two solutions -> https://stackoverflow.com/c/42network/a/1137/7740
}

double	intersect_plane(t_ray *ray, void *obj)
{
	t_plane		*plane;
	double		d_dot_n;
	double		t;

	plane = (t_plane *)obj;
	d_dot_n = dot_vec(ray->direction, plane->normal);
	t = RAY_T_MAX;
	if (d_dot_n != 0.0) // -Wfloat-equal
		t = dot_vec(plane->normal, sub_vec(plane->position, ray->origin)) / d_dot_n;
	return (t);
}

double	intersect_triangle(t_ray *ray, void *obj)
{
	t_triangle	*triangle;
	double		t;
	t_point		position;

	triangle = (t_triangle *)obj;
	t = intersect_plane(ray, &(triangle->triangle_plane));
	if (t != RAY_T_MAX) // -Wfloat-equal
	{
		position = add_vec(ray->origin, mult_vec_f(ray->direction, t));
		if (dot_vec(triangle->normal, cross_vec(triangle->edge1,
						sub_vec(position, triangle->vertex1))) > 0.0 &&// ou >=? voir square pb
				dot_vec(triangle->normal, cross_vec(triangle->edge2,
						sub_vec(position, triangle->vertex2))) > 0.0 &&
				dot_vec(triangle->normal, cross_vec(triangle->edge3,
						sub_vec(position, triangle->vertex3))) > 0.0)
			return (t);
	}
	return (RAY_T_MAX);
}

double	intersect_square(t_ray *ray, void *obj)
{
	t_square	*square;
	double		t;

	square = (t_square *)obj;
	t = intersect_triangle(ray, &(square->triangle1));
	if (t != RAY_T_MAX) // -Wfloat-equal
		return (t);
	else
	{
		t = intersect_triangle(ray, &(square->triangle2));
		if (t != RAY_T_MAX) // -Wfloat-equal
			return (t);
	}
	return (RAY_T_MAX);
}

double	intersect_cylinder(t_ray *ray, void *obj)
{
	t_cylinder	*cylinder;
	double		t;
	t_vector	rayorigin_middle;//////
	t_vector	ad_cross_d;
	t_vector	ad_cross_oam;//////
	double		a;
	double		half_b;
	double		c;//////
	double		discriminant;
	t_point		position;
	double		distance_on_the_axis;

	cylinder = (t_cylinder *)obj;
	rayorigin_middle = sub_vec(cylinder->axis_middle, ray->origin);//////
	ad_cross_d = cross_vec(cylinder->axis_direction, ray->direction);
	ad_cross_oam = cross_vec(cylinder->axis_direction, rayorigin_middle);//////
	a = length_squared_vec(ad_cross_d);
	half_b = -1.0 * dot_vec(ad_cross_d, ad_cross_oam);
	c = length_squared_vec(ad_cross_oam) - sq(cylinder->radius);//////
	discriminant = sq(half_b) - a * c;
	if (discriminant >= 0.0)
	{
		t = (-1.0 * half_b - sqrt(discriminant)) / a;
		if (t >= RAY_T_MIN)
		{
			position = add_vec(ray->origin, mult_vec_f(ray->direction, t));
			distance_on_the_axis = dot_vec(cylinder->axis_direction,
					sub_vec(position, rayorigin_middle));
			if (distance_on_the_axis <= cylinder->height / 2.0 &&
					distance_on_the_axis >= cylinder->height / -2.0)
			{
				cylinder->surface_side = OUTSIDE;
				return (t);
			}
		}
		t = (-1.0 * half_b + sqrt(discriminant)) / a;
		position = add_vec(ray->origin, mult_vec_f(ray->direction, t));
		distance_on_the_axis = dot_vec(cylinder->axis_direction,
				sub_vec(position, rayorigin_middle));
		if (distance_on_the_axis <= cylinder->height / 2.0 &&
				distance_on_the_axis >= cylinder->height / -2.0)
		{
			cylinder->surface_side = INSIDE;
			return (t);
		}
	}
	return (RAY_T_MAX);
}
