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
	t_vector	rayorigin_spcentre;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t;

	sp = (t_sphere *)obj;
	rayorigin_spcentre = sub_vec(ray->origin, sp->centre);// a mettre en cache? ->liste chainee dans sp
	//ray.direction = sub_vec(ray.direction, ray.origin);
	a = dot_vec(ray->direction, ray->direction);
	b = 2 * dot_vec(ray->direction, rayorigin_spcentre);
	c = dot_vec(rayorigin_spcentre, rayorigin_spcentre) - sq(sp->radius);
	discriminant = sq(b) - 4 * a * c; // 4c a mettre en cache?
	if (discriminant < 0.0)
		t = RAY_T_MAX;
	else
		t = (-1 * b - sqrt(discriminant)) / (2 * a);
	return (t);
	// two solutions? (inside spheres?)
	//if (discriminant < 0.0)
	//	return (RAY_T_MAX);
	//else
	//{
	//	t1 = (-1 * b - sqrt(discriminant)) / (2 * a);
	//	t2 = (-1 * b + sqrt(discriminant)) / (2 * a);
	//}
	//return (t1 < t2 ? t1 : t2);
}

t_vector	normal_sphere(t_point position_on_the_surface, void *obj)
{
	t_sphere	*sp;
	t_vector	normal;

	sp = (t_sphere *)obj;
	normal = sub_vec(position_on_the_surface, sp->centre);
	normal = unit_vec(normal, length_vec(normal));
	//  There are two design decisions to make for normals. The first is
	//  whether these normals are unit length. That is convenient for shading
	//  so I will say yes, but I won’t enforce that in the code. This could
	//  allow subtle bugs, so be aware this is personal preference as are most
	//  design decisions like that.
	//
	//  We can set things up so that normals always point “outward” from the
	//  surface, or always point against the incident ray. This decision is
	//  determined by whether you want to determine the side of the surface at
	//  the time of geometry intersection or at the time of coloring. In this
	//  book we have more material types than we have geometry types, so we'll
	//  go for less work and put the determination at geometry time. This is
	//  simply a matter of preference, and you'll see both implementations in
	//  the literature.
	return (normal);
}

double	intersect_plane(t_ray *ray, void *obj)
{
	t_plane		*pl;
	double		d_dot_n;
	double		t;

	pl = (t_plane *)obj;
	d_dot_n = dot_vec(ray->direction, pl->normal);
	t = RAY_T_MAX;
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

