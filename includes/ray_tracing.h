/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:55:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:38:43 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include "mlx_handling.h"
# include "bmp_export.h"
# include "vectors.h"
# include "minirt.h"

# define UPGUIDE	(t_vector){0.0, 1.0, 0.0}
# define RAY_T_MIN	0.0001
# define RAY_T_MAX	1.0e30

# define INSIDE		0
# define OUTSIDE	1

# define ALBEDO 0.18
# define GAMMA 2.2

# define LITTLE_ENDIAN_ 0
# define BIG_ENDIAN_ 1

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

typedef void		(*t_properties)(t_camera *, void *);
typedef double		(*t_equations)(t_ray *, void *);
typedef t_vector	(*t_normal)(t_point, void *);

void		pixel_put_bmp_little_endian(char *pixel_pos, int color);
void		uint_to_str_little_endian(unsigned nb, char *str);
void		pixel_put_mlx_image(t_mlx_image *image, size_t x, size_t y, unsigned color);

double		intersect_sphere(t_ray *ray, void *obj);
double		intersect_plane(t_ray *ray, void *obj);
double		intersect_square(t_ray *ray, void *obj);
double		intersect_triangle(t_ray *ray, void *obj);
double		intersect_cylinder(t_ray *ray, void *obj);

t_vector	normal_sphere(t_point position, void *obj);
t_vector	normal_plane(t_point position, void *obj);
t_vector	normal_square(t_point position, void *obj);
t_vector	normal_triangle(t_point position, void *obj);
t_vector	normal_cylinder(t_point position_on_the_surface, void *obj);

t_intersection	closest_intersection(t_ray ray, t_list *obj, double t_min, double t_max);
t_bool	intersection_or_not(t_ray ray, t_list *obj, double t_min, double t_max);

t_bool	shadows(t_point cur_pos, t_vector light_dir, t_list *objects);
t_rgb	lighting(t_point cur_pos, t_obj_wrapper *obj_wrapper, t_global *data);

void	calc_view_properties(t_global *data, t_camera *cur_camera, t_view_properties *props);
void	calc_scene_properties(t_global *data);
int		process_pixel(t_ray ray, t_global *data);
void	next_pixel_x(t_view_properties *props);
void	next_row_y(t_view_properties *props);
void	fill_mlx_image(t_global *data, t_mlx_image *cur_image, t_camera *cur_camera);

#endif
