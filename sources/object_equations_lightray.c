#include "ray_tracing.h"

double	intersect_sphere_lightray(t_ray *ray, void *obj, double t)
{
	t_sphere	*sphere;
	t_vector	centre_rayorigin;
	double		a;
	double		half_b;
	double		discriminant;

	sphere = (t_sphere *)obj;
	centre_rayorigin = sub_vec(ray->origin, sphere->centre);
	a = length_squared_vec(ray->direction);
	half_b = dot_vec(ray->direction, centre_rayorigin);
	discriminant = sq(half_b) - a *
		(length_squared_vec(centre_rayorigin) - sq(sphere->radius));
	if (discriminant >= 0.0)
	{
		if (sphere->surface_side == OUTSIDE)
			t = (-1.0 * half_b - sqrt(discriminant)) / a;
		else
			t = (-1.0 * half_b + sqrt(discriminant)) / a;
		return (t);
	}
	return (FALSE);
}

double	intersect_plane_lightray(t_ray *ray, void *obj, double t)
{
	t_plane		*plane;
	double		d_dot_n;
	t_vector	rayorigin_planeposition;
	double		n_dot_op;

	plane = (t_plane *)obj;
	d_dot_n = dot_vec(ray->direction, plane->normal);
	if (d_dot_n >= EPSILON || d_dot_n <= EPSILON_NEG)
	{
		rayorigin_planeposition = sub_vec(plane->position, ray->origin);
		n_dot_op = dot_vec(plane->normal, rayorigin_planeposition);
		t = n_dot_op / d_dot_n;
		return (t);
	}
	return (FALSE);
}

double	intersect_triangle_lightray(t_ray *ray, void *obj, double t)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)obj;
	t = intersect_plane_lightray(ray, &(triangle->plane), t);
	if (t >= EPSILON)
	{
		t = extract_triangle_from_plane(t, ray, triangle);
		return (t);
	}
	return (FALSE);
}

double	intersect_square_lightray(t_ray *ray, void *obj, double t)
{
	t_square	*square;

	square = (t_square *)obj;
	t = intersect_triangle_lightray(ray, &(square->triangle1), t);
	if (t >= EPSILON)
		return (t);
	else
	{
		t = intersect_triangle_lightray(ray, &(square->triangle2), t);
		if (t >= EPSILON)
			return (t);
	}
	return (FALSE);
}

double	intersect_cylinder_lightray(t_ray *ray, void *obj, double t)
{
	t_cylinder	*cylinder;
	t_vector	rayorigin_middle;
	double		a;
	double		half_b;
	double		discriminant;

	cylinder = (t_cylinder *)obj;
	a = 0.0;
	half_b = 0.0;
	discriminant = calc_raycylinder_discriminant(ray, &a, &half_b,
			cylinder);
	if (discriminant >= 0.0 && a >= EPSILON)
	{
		rayorigin_middle = sub_vec(cylinder->axis_middle, ray->origin);
		t = (-1.0 * half_b - sqrt(discriminant)) / a;
		t = truncate_cylinder_lightray(t, ray, rayorigin_middle, cylinder);
		if (t >= EPSILON)
			return (t);
		t = (-1.0 * half_b + sqrt(discriminant)) / a;
		t = truncate_cylinder_lightray(t, ray, rayorigin_middle, cylinder);
		return (t);
	}
	return (FALSE);
}
