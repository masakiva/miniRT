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

double	intersect_sphere(t_ray *ray, void *obj, double t)
{
	t_sphere	*sphere;
	double		a;
	double		half_b;
	double		discriminant;

	sphere = (t_sphere *)obj;
	a = length_squared_vec(ray->direction);
	half_b = dot_vec(ray->direction, sphere->centre_rayorigin);
	discriminant = sq(half_b) - a * sphere->c;
	if (discriminant >= 0.0)
	{
		if (sphere->surface_side == OUTSIDE)
			t = (-1.0 * half_b - sqrt(discriminant)) / a;
		else
			t = (-1.0 * half_b + sqrt(discriminant)) / a;
		return (t);
	}
	return (FALSE);
}

double	intersect_plane(t_ray *ray, void *obj, double t)
{
	t_plane		*plane;
	double		d_dot_n;

	plane = (t_plane *)obj;
	d_dot_n = dot_vec(ray->direction, plane->normal);
	if (d_dot_n >= EPSILON || d_dot_n <= EPSILON_NEG)
	{
		t = plane->n_dot_op / d_dot_n;
		return (t);
	}
	return (FALSE);
}

double	intersect_triangle(t_ray *ray, void *obj, double t)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)obj;
	t = intersect_plane(ray, &(triangle->plane), t);
	if (t >= EPSILON)
	{
		t = extract_triangle_from_plane(t, ray, triangle);
		return (t);
	}
	return (FALSE);
}

double	intersect_square(t_ray *ray, void *obj, double t)
{
	t_square	*square;

	square = (t_square *)obj;
	t = intersect_triangle(ray, &(square->triangle1), t);
	if (t >= EPSILON)
		return (t);
	else
	{
		t = intersect_triangle(ray, &(square->triangle2), t);
		if (t >= EPSILON)
			return (t);
	}
	return (FALSE);
}

double	intersect_cylinder(t_ray *ray, void *obj, double t)
{
	t_cylinder	*cylinder;
	t_vector	ad_cross_d;
	double		a;
	double		half_b;
	double		discriminant;

	cylinder = (t_cylinder *)obj;
	ad_cross_d = cross_vec(cylinder->axis_direction, ray->direction);
	a = length_squared_vec(ad_cross_d);
	half_b = -1.0 * dot_vec(ad_cross_d, cylinder->ad_cross_oam);
	discriminant = sq(half_b) - a * cylinder->c;
	if (discriminant >= 0.0 && a >= EPSILON)
	{
		t = (-1.0 * half_b - sqrt(discriminant)) / a;
		cylinder->surface_side = OUTSIDE;
		t = truncate_cylinder(t, ray, cylinder);
		if (t >= EPSILON)
			return (t);
		t = (-1.0 * half_b + sqrt(discriminant)) / a;
		cylinder->surface_side = INSIDE;
		t = truncate_cylinder(t, ray, cylinder);
		return (t);
	}
	return (FALSE);
}
