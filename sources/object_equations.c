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
	// inside spheres : lighting: if n_dot_l is negative?
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
	if (d_dot_n != 0) // -Wfloat-equal
		t = dot_vec(pl->normal, sub_vec(pl->position, ray->origin)) / d_dot_n;
	return (t);
}

double	intersect_square(t_ray *ray, void *obj)
{
	t_square	*sq;
	t_vector	half_horizontal_side;
	t_vector	half_vertical_side;
	t_point		vertex1;
	t_point		vertex2;
	t_point		vertex3;
	t_point		vertex4;
	double		t;

	// normal cannot be vertical
	(void)ray;
	t = RAY_T_MAX;
	sq = (t_square *)obj;
	half_horizontal_side = cross_vec(sq->normal, (t_vector){0.0, 1.0, 0.0});
	half_horizontal_side = mult_vec_f(unit_vec(half_horizontal_side,
				length_vec(half_horizontal_side)), sq->side_len / 2);
	half_vertical_side = cross_vec(half_horizontal_side, sq->normal);
	half_vertical_side = mult_vec_f(unit_vec(half_vertical_side,
				length_vec(half_vertical_side)), sq->side_len / 2);
	vertex1 = sub_vec(sub_vec(sq->centre, half_horizontal_side), half_vertical_side);
	vertex2 = sub_vec(add_vec(sq->centre, half_horizontal_side), half_vertical_side);
	vertex3 = add_vec(sub_vec(sq->centre, half_horizontal_side), half_vertical_side);
	vertex4 = add_vec(add_vec(sq->centre, half_horizontal_side), half_vertical_side);
	t_triangle tr1 = {vertex1, vertex2, vertex3};
	t_triangle tr2 = {vertex2, vertex3, vertex4};
	t = intersect_triangle(ray, &tr1);
	if (t != RAY_T_MAX) // -Wfloat-equal
		return (t);
	else
	{
		t = intersect_triangle(ray, &tr2);
		if (t != RAY_T_MAX) // -Wfloat-equal
			return (t);
	}
	return (RAY_T_MAX);
}

double	intersect_triangle(t_ray *ray, void *obj)
{
	t_triangle	*tr;
	double		t;
	t_vector	edge1;
	t_vector	edge2;
	t_vector	edge3;
	t_vector	normal;
	double		d_dot_n;
	t_point		position;

	tr = (t_triangle *)obj;
	edge1 = sub_vec(tr->vertex2, tr->vertex1);
	edge2 = sub_vec(tr->vertex3, tr->vertex2);
	edge3 = sub_vec(tr->vertex1, tr->vertex3);
	normal = cross_vec(edge1, neg_vec(edge3));
	d_dot_n = dot_vec(ray->direction, normal);
	if (d_dot_n != 0) // -Wfloat-equal
	{
		t = dot_vec(normal, sub_vec(tr->vertex1, ray->origin)) / d_dot_n;
		position = add_vec(ray->origin, mult_vec_f(ray->direction, t));
		if (dot_vec(normal, cross_vec(edge1, sub_vec(position, tr->vertex1))) > 0 &&
			dot_vec(normal, cross_vec(edge2, sub_vec(position, tr->vertex2))) > 0 &&
			dot_vec(normal, cross_vec(edge3, sub_vec(position, tr->vertex3))) > 0)
			return (t);
		else
			return (RAY_T_MAX);
	}
	return (RAY_T_MAX);
}
