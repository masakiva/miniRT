/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:48:30 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 14:23:50 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HANDLING_H
# define MLX_HANDLING_H

# include <stdlib.h>
# include <errno.h>
# include "mlx.h"

# include "ray_tracing.h"
# include "errors.h"
# include "minirt.h"

# define MLX_WINDOW_TITLE "miniRT"
# define NEXT_IMAGE		1
# define PREVIOUS_IMAGE	-1
# define SAME_IMAGE		0

# ifdef PLATFORM_LINUX
#  define KEYCODE_ESCAPE 65307
#  define KEYCODE_RIGHT_ARROW 65363
#  define KEYCODE_LEFT_ARROW 65361
#  define X_EVENT_RED_CROSS 33
# endif

# ifdef PLATFORM_MACOS
#  define KEYCODE_ESCAPE 53
#  define KEYCODE_RIGHT_ARROW 124
#  define KEYCODE_LEFT_ARROW 123
#  define X_EVENT_RED_CROSS 17
# endif

unsigned	convert_color(void *mlx_ptr, int color);
int			key_hooks(int keycode, t_global *data);
t_mlx_image	*new_image(t_global *data);
t_bool		draw_images(t_global *data);
void		check_resolution(t_global *data);
void		switch_camera(t_global *data, int8_t order);
void		quit_program(t_global *data) __attribute__ ((noreturn));
int			key_hooks(int keycode, t_global *data);
int			refresh_window(t_global *data);
int			red_cross_hook(t_global *data);
void		render_with_mlx(t_global *data);

#endif
