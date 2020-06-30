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

double	truncate_cylinder(double t, t_ray *ray, t_cylinder *cylinder)
{
	if (t >= EPSILON)
	{
		cylinder->axismiddle_intersectionpoint =
			sub_vec(mult_vec_f(ray->direction, t), cylinder->rayorigin_middle);
		cylinder->distance_on_the_axis = dot_vec(cylinder->axis_direction,
				cylinder->axismiddle_intersectionpoint);
		if (cylinder->distance_on_the_axis <= cylinder->height / 2.0 &&
				cylinder->distance_on_the_axis >= cylinder->height / -2.0)
			return (t);
	}
	return (FALSE);
}

double	truncate_cylinder2(double t, t_ray *ray, t_vector rayorigin_middle,
		t_cylinder *cylinder)
{
	t_vector	axismiddle_intersectionpoint;
	double		distance_on_the_axis;

	if (t >= EPSILON)
	{
		axismiddle_intersectionpoint = sub_vec(mult_vec_f(ray->direction, t),
				rayorigin_middle);
		distance_on_the_axis = dot_vec(cylinder->axis_direction,
				axismiddle_intersectionpoint);
		if (distance_on_the_axis <= cylinder->height / 2.0 &&
				distance_on_the_axis >= cylinder->height / -2.0)
			return (t);
	}
	return (FALSE);
}

double	calc_raycylinder_discriminant(t_vector rayorigin_middle, double *a,
		double *half_b, t_cylinder *cylinder)
{
	t_vector	ad_cross_d;
	t_vector	ad_cross_oam;
	double		c;
	double		discriminant;

	ad_cross_d = cross_vec(cylinder->axis_direction, ray->direction);
	ad_cross_oam = cross_vec(cylinder->axis_direction, rayorigin_middle);
	*a = length_squared_vec(ad_cross_d);
	*half_b = -1.0 * dot_vec(ad_cross_d, ad_cross_oam);
	c = length_squared_vec(ad_cross_oam) - sq(cylinder->radius);
	discriminant = sq(*half_b) - *a * c;
	return (discriminant);
}

double	intersect_cylinder_lightray(t_ray *ray, void *obj, double t)
{
	t_cylinder	*cylinder;
	t_vector	rayorigin_middle;
	double		a;
	double		half_b;
	double		discriminant;

	cylinder = (t_cylinder *)obj;
	rayorigin_middle = sub_vec(cylinder->axis_middle, ray->origin);
	a = 0.0;
	half_b = 0.0;
	discriminant = calc_raycylinder_discriminant(rayorigin_middle, &a, &half_b,
			cylinder);
	if (discriminant >= 0.0 && a >= EPSILON)
	{
		t = (-1.0 * half_b - sqrt(discriminant)) / a;
		t = truncate_cylinder2(t, ray, rayorigin_middle, cylinder);
		if (t >= EPSILON)
			return (t);
		t = (-1.0 * half_b + sqrt(discriminant)) / a;
		t = truncate_cylinder2(t, ray, rayorigin_middle, cylinder);
		return (t);
	}
	return (FALSE);
}
