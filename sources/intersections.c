/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:46 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 13:55:37 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_bool			intersection_or_not(t_ray ray, t_list *obj_iter, double t_min,
		double t_max)
{
	static t_equations	find_t[NB_OBJ] = {intersect_sphere, intersect_plane,
		intersect_triangle, intersect_square, NULL};
	double				cur_t;
	t_obj_wrapper		*cur_obj;

	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		cur_t = find_t[cur_obj->type](&ray, cur_obj->obj);
		if (cur_t >= t_min && cur_t < t_max) // et s'il y a deux memes t
			return (TRUE);
		obj_iter = obj_iter->next;
	}
	return (FALSE);
}

t_intersection	closest_intersection(t_ray ray, t_list *obj_iter, double t_min,
		double t_max)
{
	static t_equations	find_t[NB_OBJ] = {intersect_sphere, intersect_plane,
		intersect_triangle, intersect_square, NULL};
	double				cur_t;
	t_obj_wrapper		*cur_obj;
	t_obj_wrapper		*closest_obj;
	double				closest_t;

	closest_t = t_max;
	closest_obj = NULL;
	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		cur_t = find_t[cur_obj->type](&ray, cur_obj->obj);
		if (cur_t >= t_min && cur_t < closest_t) // et s'il y a deux memes t
		{
			closest_t = cur_t;
			closest_obj = cur_obj;
		}
		obj_iter = obj_iter->next;
	}
	return ((t_intersection){closest_obj, closest_t});
}
