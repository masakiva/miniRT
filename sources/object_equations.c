/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_equations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:56:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:56:30 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

double	intersect_sphere(t_ray *ray, void *obj)
{
	t_sphere	*sp;
	t_vector	OC;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t;

	sp = (t_sphere *)obj;
	OC = sub_vec(ray->origin, sp->centre);// a mettre en cache? ->liste chainee dans sp
	//ray.direction = sub_vec(ray.direction, ray.origin);
	a = dot_vec(ray->direction, ray->direction);
	b = 2 * dot_vec(ray->direction, OC);
	c = dot_vec(OC, OC) - sq(sp->radius);
	discriminant = sq(b) - 4 * a * c; // 4c a mettre en cache?
	if (discriminant < 0.0)
		t = 2147483647;
	else
		t = (-1 * b - sqrt(discriminant)) / (2 * a);
	return (t);
}

t_vector	normal_sphere(t_point position_on_the_surface, void *obj)
{
	t_sphere	*sp;
	t_vector	normal;

	sp = (t_sphere *)obj;
	normal = sub_vec(position_on_the_surface, sp->centre);
	normal = unit_vec(normal, length_vec(normal));
	return (normal);
}

double	intersect_plane(t_ray *ray, void *obj)
{
	t_plane		*pl;
	double		d_dot_n;
	double		t;

	pl = (t_plane *)obj;
	d_dot_n = dot_vec(ray->direction, pl->normal);
	t = 2147483647;
	if (d_dot_n != 0)
	{
		t = dot_vec(pl->normal, sub_vec(pl->position, ray->origin)) / d_dot_n;
	}
	return (t);
}

t_vector	normal_plane(t_point position, void *obj)
{
	(void)position;
	return (((t_plane *)obj)->normal);
}

