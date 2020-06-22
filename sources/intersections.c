/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:46 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:39:47 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_intersection	closest_intersection(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[2/*NB_OBJ*/] = {intersect_sphere, intersect_plane/*,
		intersect_square, intersect_cylinder, intersect_triangle*/};
	double			cur_t;
	t_obj			*cur_obj;
	t_list			*closest_elem;
	double			closest_t;

	closest_t = t_max;
	closest_elem = NULL;
	while (obj != NULL)
	{
		cur_obj = (t_obj *)obj->content;
		cur_t = find_t[cur_obj->type](&ray, cur_obj->obj);
		if (cur_t >= t_min && cur_t < closest_t) // ou >= 1? ; et s'il y a deux memes t
		{
			closest_t = cur_t;
			closest_elem = obj;
		}
		obj = obj->next;
	}
	return ((t_intersection){closest_elem, closest_t});
}

t_bool	intersection_or_not(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[2/*NB_OBJ*/] = {intersect_sphere, intersect_plane/*,
		intersect_square, intersect_cylinder, intersect_triangle*/};
	double			cur_t;

	while (obj != NULL)
	{
		cur_t = find_t[((t_obj *)obj->content)->type](&ray, ((t_obj *)obj->content)->obj);
		if (cur_t >= t_min && cur_t < t_max) // ou >= 1? ; et s'il y a deux memes t
			return (TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

