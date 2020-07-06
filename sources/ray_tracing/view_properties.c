/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:21:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:21:54 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

static void	camera_properties(t_global *data, t_camera *cur_camera,
		t_view_properties *props)
{
	props->right_vec = cross_vec(g_upguide, cur_camera->direction);
	props->right_vec = unit_vec(props->right_vec, length_vec(props->right_vec));
	props->up_vec = cross_vec(cur_camera->direction, props->right_vec);
	props->up_vec = unit_vec(props->up_vec, length_vec(props->up_vec));
	props->half_width = tan((M_PI * (double)cur_camera->fov / 180.0) / 2.0);
	props->half_height = props->half_width *
		((double)data->res[HEIGHT] / (double)data->res[WIDTH]);
	props->half_pixel_width = props->half_width / (double)data->res[WIDTH];
	props->x_factor = -1.0;
	props->x_factor_i = 2.0 / (double)data->res[WIDTH];
	props->x_factor_vec = mult_vec_f(props->right_vec,
			props->x_factor * props->half_width + props->half_pixel_width);
	props->y_factor = 1.0;
	props->y_factor_i = 2.0 / (double)data->res[HEIGHT];
	props->y_factor_vec = mult_vec_f(props->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
}

void		calc_view_properties(t_global *data, t_camera *cur_camera,
		t_view_properties *props)
{
	static t_properties	obj_properties[NB_OBJ] = {sphere_view_properties,
		plane_view_properties, triangle_view_properties, square_view_properties,
		cylinder_view_properties};
	t_list				*obj_iter;
	t_obj_wrapper		*cur_obj;

	camera_properties(data, cur_camera, props);
	obj_iter = data->objects;
	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		obj_properties[cur_obj->type](cur_camera, cur_obj->obj);
		obj_iter = obj_iter->next;
	}
}
