/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:21:58 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:21:59 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

static void	triangle_scene_properties(void *obj)
{
	t_triangle		*triangle;

	triangle = (t_triangle *)obj;
	triangle->edge1 = sub_vec(triangle->vertex2, triangle->vertex1);
	triangle->edge2 = sub_vec(triangle->vertex3, triangle->vertex2);
	triangle->edge3 = sub_vec(triangle->vertex1, triangle->vertex3);
	triangle->normal = cross_vec(triangle->edge1, neg_vec(triangle->edge3));
	triangle->normal = unit_vec(triangle->normal, length_vec(triangle->normal));
	triangle->plane.position = triangle->vertex1;
	triangle->plane.normal = triangle->normal;
}

static void	get_square_triangles_vertices(t_vector half_horizontal_side,
		t_vector half_vertical_side, t_square *square)
{
	t_point		vertex1;
	t_point		vertex2;
	t_point		vertex3;
	t_point		vertex4;

	vertex1 = sub_vec(sub_vec(square->centre, half_horizontal_side),
			half_vertical_side);
	vertex2 = sub_vec(add_vec(square->centre, half_horizontal_side),
			half_vertical_side);
	vertex3 = add_vec(sub_vec(square->centre, half_horizontal_side),
			half_vertical_side);
	vertex4 = add_vec(add_vec(square->centre, half_horizontal_side),
			half_vertical_side);
	square->triangle1.vertex1 = vertex1;
	square->triangle1.vertex2 = vertex2;
	square->triangle1.vertex3 = vertex3;
	square->triangle2.vertex1 = vertex2;
	square->triangle2.vertex2 = vertex3;
	square->triangle2.vertex3 = vertex4;
}

static void	square_scene_properties(void *obj)
{
	t_square	*square;
	t_vector	half_horizontal_side;
	t_vector	half_vertical_side;

	square = (t_square *)obj;
	half_horizontal_side = cross_vec(square->normal, g_upguide);
	half_horizontal_side = mult_vec_f(unit_vec(half_horizontal_side,
				length_vec(half_horizontal_side)), square->side_len / 2.0);
	half_vertical_side = cross_vec(half_horizontal_side, square->normal);
	half_vertical_side = mult_vec_f(unit_vec(half_vertical_side,
				length_vec(half_vertical_side)), square->side_len / 2.0);
	get_square_triangles_vertices(half_horizontal_side, half_vertical_side,
			square);
	triangle_scene_properties(&(square->triangle1));
	triangle_scene_properties(&(square->triangle2));
}

void		calc_scene_properties(t_global *data)
{
	t_list				*obj_iter;
	t_obj_wrapper		*cur_obj;

	obj_iter = data->objects;
	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		if (cur_obj->type == TRIANGLE)
			triangle_scene_properties(cur_obj->obj);
		else if (cur_obj->type == SQUARE)
			square_scene_properties(cur_obj->obj);
		obj_iter = obj_iter->next;
	}
}
