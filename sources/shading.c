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

t_bool	shadows(t_point cur_pos, t_vector light_dir, t_list *objects)
{
	t_ray	light_ray;
	double	light_dir_length;

	light_ray.origin = cur_pos;
	light_dir_length = length_vec(light_dir);
	light_ray.direction = unit_vec(light_dir, light_dir_length);
	if (intersection_or_not(light_ray, objects, RAY_T_MIN, light_dir_length - /*ou +?*/ RAY_T_MIN) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

t_rgb	lighting(t_point cur_pos, t_obj_wrapper *obj_wrapper, t_global *data)
{
	static t_normal	calc_normal[NB_OBJ] = {normal_sphere, normal_plane,
		normal_triangle, normal_square, normal_cylinder};
	t_vector		normal;
	t_light			*cur_light;
	t_list			*lights_iter;
	t_vector		light_dir;
	double			light_dir_length;
	double			n_dot_l;
	t_rgb			color;

	if (data->lights != NULL)
		normal = calc_normal[obj_wrapper->type](cur_pos, obj_wrapper->obj);
	color = (t_rgb){0.0, 0.0, 0.0};
	lights_iter = data->lights;
	while (lights_iter != NULL)
	{
		cur_light = (t_light *)lights_iter->content;
		light_dir = sub_vec(cur_light->position, cur_pos);
		n_dot_l = dot_vec(normal, light_dir);
		if (n_dot_l >= RAY_T_MIN && shadows(cur_pos, light_dir, data->objects) == FALSE)
		{
			light_dir_length = length_vec(light_dir);
			n_dot_l /= light_dir_length;//premier inutile si unitaire
			color = add_vec(color, mult_vec_f(cur_light->color,
						n_dot_l)); // / (4 * M_PI * sq(light_dir_length))));
		}
		lights_iter = lights_iter->next;
	}
	color = add_vec(color, data->ambient_light_color);
	//color = mult_vec_f(color, ALBEDO / M_PI);
	return (color);
}

