/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ah <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:08:28 by ah                #+#    #+#             */
/*   Updated: 2020/07/06 21:43:36 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_MANAGEMENT_H
# define DATA_MANAGEMENT_H

# define LITTLE_ENDIAN_	0
# define BIG_ENDIAN_	1

# include <math.h>

# include "errors.h"

void	free_data(t_global *data);
t_bool	add_to_list(void *cur_object, t_list **lst);

/*
** pixel put, color utils
*/

void	pixel_put_bmp_little_endian(char *pixel_pos, int color);
void	uint_to_str_little_endian(unsigned nb, char *str);
void	pixel_put_mlx_image(t_mlx_image *image, size_t x, size_t y,
		unsigned color);
int		rgb_to_int(t_rgb color);

#endif
