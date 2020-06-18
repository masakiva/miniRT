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

double		i_sphere(t_ray *ray, void *obj);
t_vector	n_sphere(t_point position, void *obj);
double		i_plane(t_ray *ray, void *obj);
t_vector	n_plane(t_point position, void *obj);

void	get_view_properties(t_global *data, t_view_properties *props, t_camera *cur_camera);
void	fill_mlx_image(t_global *data, t_image *cur_image, t_camera *cur_camera);
void	fill_bmp_data(t_global *data, char *file_data, size_t line_padding);

#endif