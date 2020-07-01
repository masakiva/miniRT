/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:40:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 14:02:42 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_bool			shadow_obstacle(t_ray ray, t_list *obj_iter)
{
	static t_equations	find_t[NB_OBJ] = {intersect_sphere_lightray,
		intersect_plane_lightray, intersect_triangle_lightray,
		intersect_square_lightray, intersect_cylinder_lightray};
	double				cur_t;
	t_obj_wrapper		*cur_obj;

	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		cur_t = find_t[cur_obj->type](&ray, cur_obj->obj, 0.0);
		if (cur_t >= EPSILON && cur_t <= 1 - EPSILON)
			return (TRUE);
		obj_iter = obj_iter->next;
	}
	return (FALSE);
}

t_vector	calc_normal(t_obj_wrapper *obj_wrapper, t_point cur_pos)
{
	static t_normal	calc_normal[NB_OBJ] = {normal_sphere, normal_plane,
		normal_triangle, normal_square, normal_cylinder};
	t_vector		normal;

	normal = calc_normal[obj_wrapper->type](cur_pos, obj_wrapper->obj);
	return (normal);
}

t_rgb	lighting(t_point cur_pos, t_obj_wrapper *obj_wrapper, t_global *data,
		t_rgb light_color)
{
	t_vector		normal;
	t_light			*cur_light;
	t_list			*lights_iter;
	t_vector		light_dir;
	double			n_dot_l;

	if (data->lights != NULL)
		normal = calc_normal(obj_wrapper, cur_pos);
	lights_iter = data->lights;
	while (lights_iter != NULL)
	{
		cur_light = (t_light *)lights_iter->content;
		light_dir = sub_vec(cur_light->position, cur_pos);
		n_dot_l = dot_vec(normal, unit_vec(light_dir, length_vec(light_dir)));
		if (n_dot_l >= EPSILON && shadow_obstacle((t_ray){cur_pos, light_dir},
					data->objects) == FALSE)
			light_color = add_vec(light_color,
					mult_vec_f(cur_light->color, n_dot_l)); // / (4 * M_PI * sq(light_dir_length))));
		lights_iter = lights_iter->next;
	}
	light_color = add_vec(light_color, data->ambient_light_color);
	//light_color = mult_vec_f(light_color, ALBEDO / M_PI);
	return (light_color);
}

