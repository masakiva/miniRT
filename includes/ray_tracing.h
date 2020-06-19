/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:55:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:57:35 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include <math.h>

# include "mlx_handling.h"
# include "bmp_export.h"
# include "vectors.h"
# include "minirt.h"

# define RAY_T_MIN	0.0001
# define RAY_T_MAX	1.0e30

# define GAMMA 2.2

# define LITTLE_ENDIAN_ 0
# define BIG_ENDIAN_ 1

double		intersect_sphere(t_ray *ray, void *obj);
t_vector	normal_sphere(t_point position, void *obj);
double		intersect_plane(t_ray *ray, void *obj);
t_vector	normal_plane(t_point position, void *obj);

void	get_view_properties(t_global *data, t_view_properties *props, t_camera *cur_camera);
void	fill_mlx_image(t_global *data, t_image *cur_image, t_camera *cur_camera);
void	fill_bmp_data(t_global *data, char *file_data, size_t line_padding);

#endif
