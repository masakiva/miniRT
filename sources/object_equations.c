/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_equations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:56:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:39:09 by mvidal-a         ###   ########.fr       */
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
	a = dot_vec(ray->direction, ray->direction);
	b = 2 * dot_vec(ray->direction, rayorigin_spcentre);
	c = dot_vec(rayorigin_spcentre, rayorigin_spcentre) - sq(sp->radius);
	discriminant = sq(b) - 4 * a * c; // 4c a mettre en cache?
	if (discriminant < 0.0)
		t = RAY_T_MAX;
	else
		t = (-1 * b - sqrt(discriminant)) / (2 * a);// div par zero si ray->direction = 0
	return (t);
	// two solutions -> https://stackoverflow.com/c/42network/a/1137/7740
	//if (discriminant < 0.0)
	//	return (RAY_T_MAX);
	//else
	//{
	//	t1 = (-1 * b - sqrt(discriminant)) / (2 * a);
	//	t2 = (-1 * b + sqrt(discriminant)) / (2 * a);
	//}
	//return (t1 < t2 ? t1 : t2);
}

double	intersect_plane(t_ray *ray, void *obj)
{
	t_plane		*pl;
	double		d_dot_n;
	double		t;

	pl = (t_plane *)obj;
	d_dot_n = dot_vec(ray->direction, pl->normal);
	t = RAY_T_MAX;
	if (d_dot_n >= RAY_T_MIN)
		t = dot_vec(pl->normal, sub_vec(pl->position, ray->origin)) / d_dot_n;
	return (t);
}
