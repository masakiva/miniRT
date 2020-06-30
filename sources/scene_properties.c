#include "ray_tracing.h"

void	camera_properties(t_global *data, t_camera *cur_camera, t_view_properties *props)
{
	props->right_vec = cross_vec(UPGUIDE, cur_camera->direction);
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

void	sphere_props(t_camera *cur_camera, void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	sphere->centre_rayorigin = sub_vec(cur_camera->origin, sphere->centre);
	if (length_vec(sphere->centre_rayorigin) >= sphere->radius)
		sphere->surface_side = OUTSIDE;
	else
		sphere->surface_side = INSIDE;
}

void	plane_props(t_camera *cur_camera, void *obj)
{
	t_plane		*plane;
	t_vector	rayorigin_planeposition;

	plane = (t_plane *)obj;
	rayorigin_planeposition = sub_vec(plane->position, cur_camera->origin);
	plane->n_dot_op = dot_vec(plane->normal, rayorigin_planeposition);
	if (dot_vec(rayorigin_planeposition, plane->normal) > 0.0)
		plane->normal = neg_vec(plane->normal);
}

void	triangle_props(t_camera *cur_camera, void *obj)// new name?
{
	t_triangle	*triangle;
	t_vector	rayorigin_triangleposition;

	triangle = (t_triangle *)obj;
	rayorigin_triangleposition = sub_vec(triangle->vertex1, cur_camera->origin);
	if (dot_vec(rayorigin_triangleposition, triangle->normal) > 0.0)
		triangle->triangle_plane.normal = neg_vec(triangle->normal);// pb
}

void	square_props(t_camera *cur_camera, void *obj)
{
	t_square	*square;
	t_vector	rayorigin_squareposition;

	square = (t_square *)obj;
	rayorigin_squareposition = sub_vec(square->centre, cur_camera->origin);
	if (dot_vec(rayorigin_squareposition, square->normal) > 0.0)
		square->normal = neg_vec(square->normal);
}

void	cylinder_props(t_camera *cur_camera, void *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)obj;
	cylinder->rayorigin_middle = sub_vec(cylinder->axis_middle,
			cur_camera->origin);
	cylinder->ad_cross_oam = cross_vec(cylinder->axis_direction,
			cylinder->rayorigin_middle);
	cylinder->c = length_squared_vec(cylinder->ad_cross_oam) -
		sq(cylinder->radius);
}

void	triangle_scene_props(void *obj)// new name?
{
	t_triangle		*triangle;

	triangle = (t_triangle *)obj;
	triangle->edge1 = sub_vec(triangle->vertex2, triangle->vertex1);
	triangle->edge2 = sub_vec(triangle->vertex3, triangle->vertex2);
	triangle->edge3 = sub_vec(triangle->vertex1, triangle->vertex3);
	triangle->normal = cross_vec(triangle->edge1, neg_vec(triangle->edge3));
	triangle->normal = unit_vec(triangle->normal, length_vec(triangle->normal));// utile?
	triangle->triangle_plane.position = triangle->vertex1;
	triangle->triangle_plane.normal = triangle->normal;
}

void	get_square_triangles_vertices(t_vector half_horizontal_side,
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

void	square_scene_props(void *obj)
{
	t_square	*square;
	t_vector	half_horizontal_side;
	t_vector	half_vertical_side;

	square = (t_square *)obj;
	half_horizontal_side = cross_vec(square->normal, UPGUIDE);
	half_horizontal_side = mult_vec_f(unit_vec(half_horizontal_side,
				length_vec(half_horizontal_side)), square->side_len / 2.0);
	half_vertical_side = cross_vec(half_horizontal_side, square->normal);
	half_vertical_side = mult_vec_f(unit_vec(half_vertical_side,
				length_vec(half_vertical_side)), square->side_len / 2.0);
	get_square_triangles_vertices(half_horizontal_side, half_vertical_side,
			square);
	triangle_scene_props(&(square->triangle1));
	triangle_scene_props(&(square->triangle2));
}

void	calc_view_properties(t_global *data, t_camera *cur_camera, t_view_properties *props)
{
	static t_properties	obj_properties[NB_OBJ] = {sphere_props, plane_props,
		triangle_props, square_props, cylinder_props};
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

void	calc_scene_properties(t_global *data)
{
	t_list				*obj_iter;
	t_obj_wrapper		*cur_obj;

	obj_iter = data->objects;
	while (obj_iter != NULL)
	{
		cur_obj = (t_obj_wrapper *)obj_iter->content;
		if (cur_obj->type == TRIANGLE)
			triangle_scene_props(cur_obj->obj);
		else if (cur_obj->type == SQUARE)
			square_scene_props(cur_obj->obj);
		obj_iter = obj_iter->next;
	}
}
