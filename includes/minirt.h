/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:24:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 11:58:52 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SUCCESS	1
# define FAILURE	0

# define TRUE	1
# define FALSE	0

# define ERROR	-1

# define WIDTH 0
# define HEIGHT 1

# define NB_OBJ	5

# include <stdlib.h>
# include "libft.h"// a inclure sorezore
#include <stdio.h>/////////////

enum	e_object
{
	SPHERE,
	PLANE,
	TRIANGLE,
	SQUARE,
	CYLINDER
};

typedef int8_t	t_bool;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef t_vector	t_point;
typedef t_vector	t_rgb;

/*
** scene utils: camera, misc properties, lights
*/

typedef struct	s_camera
{
	t_point		origin;
	t_vector	direction;
	int			fov;
	uint8_t		pad_[4];
}				t_camera;

typedef struct	s_view_properties // ici?
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

typedef struct	s_light
{
	t_point		position;
	t_rgb		color;
}				t_light;

/*
** scene objects: wrapper struct, then sphere, plane, square, etc.
*/

typedef struct	s_obj_wrapper
{
	void		*obj;
	t_rgb		color;
	uint8_t		type;
	uint8_t		pad_[7];
}				t_obj_wrapper;

typedef struct	s_sphere
{
	t_point		centre;
	double		radius;
	t_vector	centre_rayorigin;
	double		c;
	t_bool		surface_side;
	uint8_t		pad_[7];
}				t_sphere;

typedef struct	s_plane
{
	t_point		position;
	t_vector	normal;
}				t_plane;

typedef struct	s_triangle
{
	t_point		vertex1;
	t_point		vertex2;
	t_point		vertex3;
	t_vector	edge1;
	t_vector	edge2;
	t_vector	edge3;
	t_vector	normal;
	t_plane		triangle_plane;
}				t_triangle;

typedef struct	s_square
{
	t_point		centre;
	t_vector	normal;
	double		side_len;
	t_point		vertex1;
	t_point		vertex2;
	t_point		vertex3;
	t_point		vertex4;
	t_triangle	triangle1;
	t_triangle	triangle2;
}				t_square;

typedef struct	s_cylinder
{
	t_point		position;
	t_vector	normal;
	double		diameter;
	double		height;
}				t_cylinder;

/*
** minilibx image data
*/

typedef struct	s_mlx_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	uint8_t	pad_[4];
}				t_mlx_image;

/*
** global struct for all the data
*/

typedef struct	s_global
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_list		*images;
	size_t		res[2];
	t_rgb		ambient_light_color;
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
	char		*bmpfile_data;
}				t_global;

void	free_data(t_global *data);
t_bool	add_to_list(void *cur_object, t_list **lst);
t_rgb	apply_gamma_correction(t_rgb color);
void	majorize_color_channels(t_rgb *color);
int		rgb_to_int(t_rgb color);

#endif
