/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:48:30 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:51:06 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HANDLING_H
# define MLX_HANDLING_H

# define KEYCODE_ESCAPE 65307
# define KEYCODE_RIGHT_ARROW 65363
# define KEYCODE_LEFT_ARROW 65361

# define MACOS_KEYCODE_ESCAPE 53
# define MACOS_KEYCODE_RIGHT_ARROW 124
# define MACOS_KEYCODE_LEFT_ARROW 123

void			image_pixel_put(t_image *image, size_t x, size_t y, unsigned color);
void			pixel_put_converted_color(t_global *data, t_image *image, size_t px_coord[2], int color);
int				key_hooks(int keycode, t_global *data);
t_image			*new_image(t_global *data);
t_bool			draw_images(t_global *data);
void			check_resolution(t_global *data);
void			switch_camera(t_global *data, int8_t order);
void			quit_program(t_global *data);
int				key_hooks(int keycode, t_global *data);
void			render_with_mlx(t_global *data);

#endif
