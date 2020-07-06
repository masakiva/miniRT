/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:55:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:43:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include "mlx_display.h"
# include "bmp_export.h"
# include "vectors.h"
# include "data_management.h"
# include "minirt.h"

# define EPSILON		0.0001
# define EPSILON_NEG	-0.0001
# define T_MAX			1.0e30

/*
** inside or outside spheres and cylinders
*/

# define INSIDE			0
# define OUTSIDE		1

static const t_vector g_upguide = (t_vector){0.0, 1.0, 0.0};

typedef struct	s_ray
{
	t_point		origin;
	t_vector	direction;
}				t_ray;

typedef struct	s_intersection
{
	t_obj_wrapper	*obj_wrapper;
	double			t;
}				t_intersection;

/*
** scene properties for each camera
*/

typedef struct	s_view_properties
{
	t_vector	right_vec;
	t_vector	up_vec;
	double		half_width;
	double		half_height;
	double		half_pixel_width;
	double		x_factor;
	double		x_factor_i;
	t_vector	x_factor_vec;
	double		y_factor;
	double		y_factor_i;
	t_vector	y_factor_vec;
}				t_view_properties;

typedef void		(*t_properties)(t_camera *, void *);
typedef double		(*t_equations)(t_ray *, void *, double);
typedef t_vector	(*t_normal)(t_point, void *);

/*
** ray tracing algorithm
*/

t_rgb			lighting(t_point cur_pos, t_obj_wrapper *obj_wrapper,
		t_global *data, t_rgb light_color);
void			calc_view_properties(t_global *data, t_camera *cur_camera,
		t_view_properties *props);
void			calc_scene_properties(t_global *data);
void			next_pixel_x(t_view_properties *props);
void			next_row_y(t_view_properties *props);
void			fill_bmp_data(t_global *data, char *file_data,
		size_t line_padding);
void			fill_mlx_image(t_global *data, t_mlx_image *cur_image,
		t_camera *cur_camera);

/*
** object properties for each camera
*/

void			sphere_view_properties(t_camera *cur_camera, void *obj);
void			plane_view_properties(t_camera *cur_camera, void *obj);
void			triangle_view_properties(t_camera *cur_camera, void *obj);
void			square_view_properties(t_camera *cur_camera, void *obj);
void			cylinder_view_properties(t_camera *cur_camera, void *obj);

/*
** object equations, for camera rays, and for light rays
*/

double			intersect_sphere(t_ray *ray, void *obj, double t);
double			intersect_plane(t_ray *ray, void *obj, double t);
double			intersect_square(t_ray *ray, void *obj, double t);
double			intersect_triangle(t_ray *ray, void *obj, double t);
double			intersect_cylinder(t_ray *ray, void *obj, double t);

double			intersect_sphere_lightray(t_ray *ray, void *obj, double t);
double			intersect_plane_lightray(t_ray *ray, void *obj, double t);
double			intersect_triangle_lightray(t_ray *ray, void *obj, double t);
double			intersect_square_lightray(t_ray *ray, void *obj, double t);
double			intersect_cylinder_lightray(t_ray *ray, void *obj, double t);

double			extract_triangle_from_plane(double t, t_ray *ray,
		t_triangle *triangle);
double			truncate_cylinder(double t, t_ray *ray, t_cylinder *cylinder);
double			truncate_cylinder_lightray(double t, t_ray *ray,
		t_vector rayorigin_middle, t_cylinder *cylinder);
double			calc_raycylinder_discriminant(t_ray *ray, double *a,
		double *half_b, t_cylinder *cylinder);

/*
** calculate normals for each object
*/

t_vector		normal_sphere(t_point position, void *obj);
t_vector		normal_plane(t_point position, void *obj);
t_vector		normal_square(t_point position, void *obj);
t_vector		normal_triangle(t_point position, void *obj);
t_vector		normal_cylinder(t_point position_on_the_surface, void *obj);

#endif
