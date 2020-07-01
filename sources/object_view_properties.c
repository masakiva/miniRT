#include "ray_tracing.h"

void	sphere_view_properties(t_camera *cur_camera, void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	sphere->centre_rayorigin = sub_vec(cur_camera->origin, sphere->centre);
	sphere->c = length_squared_vec(sphere->centre_rayorigin) -
		sq(sphere->radius);
	if (length_vec(sphere->centre_rayorigin) >= sphere->radius)
		sphere->surface_side = OUTSIDE;
	else
		sphere->surface_side = INSIDE;
}

void	plane_view_properties(t_camera *cur_camera, void *obj)
{
	t_plane		*plane;
	t_vector	rayorigin_planeposition;

	plane = (t_plane *)obj;
	rayorigin_planeposition = sub_vec(plane->position, cur_camera->origin);
	if (dot_vec(rayorigin_planeposition, plane->normal) > 0.0)
		plane->normal = neg_vec(plane->normal);
	plane->n_dot_op = dot_vec(plane->normal, rayorigin_planeposition);
}

void	triangle_view_properties(t_camera *cur_camera, void *obj)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)obj;
	plane_view_properties(cur_camera, &(triangle->plane));
}

void	square_view_properties(t_camera *cur_camera, void *obj)
{
	t_square	*square;

	square = (t_square *)obj;
	triangle_view_properties(cur_camera, &(square->triangle1));
	triangle_view_properties(cur_camera, &(square->triangle2));
}

void	cylinder_view_properties(t_camera *cur_camera, void *obj)
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

