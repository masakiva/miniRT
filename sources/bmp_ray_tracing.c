/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_ray_tracing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:38:51 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:38:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_export.h"

void	set_bmp_pixel_color(t_camera *cur_camera, t_view_properties *props,
		t_global *data, char *pixel_pos)
{
	t_ray				ray;
	int					color;

	ray.origin = cur_camera->origin;
	ray.direction = add_vec(cur_camera->direction,
			add_vec(props->x_factor_vec, props->y_factor_vec));
	color = process_pixel(ray, data);
	pixel_put_bmp_little_endian(pixel_pos, color);
}

void	fill_bmp_data(t_global *data, char *data_addr, size_t line_padding)
{
	size_t				x;
	size_t				y;
	t_view_properties	props;
	t_camera			*cur_camera;
	size_t				i;

	cur_camera = (t_camera *)data->cameras->content;
	get_view_properties(data, &props, cur_camera);
	i = BMP_METADATA_SIZE;
	y = 0;
	while (y < data->res[HEIGHT])
	{
		i = (data->res[HEIGHT] - y - 1) * (data->res[WIDTH] * 3 + line_padding);
		x = 0;
		while (x < data->res[WIDTH])
		{
			set_bmp_pixel_color(cur_camera, &props, data, data_addr + i);
			next_pixel_x(cur_camera, &props);
			i += 3;
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
}
