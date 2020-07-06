/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_equations_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:22:05 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:22:06 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

double	extract_triangle_from_plane(double t, t_ray *ray, t_triangle *triangle)
{
	t_point		position;

	position = add_vec(ray->origin, mult_vec_f(ray->direction, t));
	if (dot_vec(triangle->normal, cross_vec(triangle->edge1,
					sub_vec(position, triangle->vertex1))) >= 0.0 &&
			dot_vec(triangle->normal, cross_vec(triangle->edge2,
					sub_vec(position, triangle->vertex2))) >= 0.0 &&
			dot_vec(triangle->normal, cross_vec(triangle->edge3,
					sub_vec(position, triangle->vertex3))) >= 0.0)
		return (t);
	return (FALSE);
}

double	truncate_cylinder(double t, t_ray *ray, t_cylinder *cylinder)
{
	if (t >= EPSILON)
	{
		cylinder->axismiddle_intersectionpoint =
			sub_vec(mult_vec_f(ray->direction, t), cylinder->rayorigin_middle);
		cylinder->distance_on_the_axis = dot_vec(cylinder->axis_direction,
				cylinder->axismiddle_intersectionpoint);
		if (cylinder->distance_on_the_axis <= cylinder->height / 2.0 &&
				cylinder->distance_on_the_axis >= cylinder->height / -2.0)
			return (t);
	}
	return (FALSE);
}

double	truncate_cylinder_lightray(double t, t_ray *ray,
		t_vector rayorigin_middle, t_cylinder *cylinder)
{
	t_vector	axismiddle_intersectionpoint;
	double		distance_on_the_axis;

	if (t >= EPSILON)
	{
		axismiddle_intersectionpoint = sub_vec(mult_vec_f(ray->direction, t),
				rayorigin_middle);
		distance_on_the_axis = dot_vec(cylinder->axis_direction,
				axismiddle_intersectionpoint);
		if (distance_on_the_axis <= cylinder->height / 2.0 &&
				distance_on_the_axis >= cylinder->height / -2.0)
			return (t);
	}
	return (FALSE);
}

double	calc_raycylinder_discriminant(t_ray *ray, double *a, double *half_b,
		t_cylinder *cylinder)
{
	t_vector	rayorigin_middle;
	t_vector	ad_cross_d;
	t_vector	ad_cross_oam;
	double		c;
	double		discriminant;

	rayorigin_middle = sub_vec(cylinder->axis_middle, ray->origin);
	ad_cross_d = cross_vec(cylinder->axis_direction, ray->direction);
	ad_cross_oam = cross_vec(cylinder->axis_direction, rayorigin_middle);
	*a = length_squared_vec(ad_cross_d);
	*half_b = -1.0 * dot_vec(ad_cross_d, ad_cross_oam);
	c = length_squared_vec(ad_cross_oam) - sq(cylinder->radius);
	discriminant = sq(*half_b) - *a * c;
	return (discriminant);
}
