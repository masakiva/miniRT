/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:24:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:42:36 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define TRUE		1
# define FALSE		0

# define SUCCESS	1
# define FAILURE	0
# define ERROR		-1

/*
** for the screen resolution two-number array
*/

# define WIDTH 	0
# define HEIGHT 1

/*
** objects that can be modelled (see following enum)
*/

# define NB_OBJ	5

# include <stdlib.h>

# include "libft.h"

enum				e_object
{
	SPHERE,
	PLANE,
	TRIANGLE,
	SQUARE,
	CYLINDER
};

typedef int8_t		t_bool;

typedef struct		s_vector
{
	double	x;
	double	y;
	double	z;
}					t_vector;

typedef t_vector	t_point;
typedef t_vector	t_rgb;

/*
** scene elements: cameras, lights
*/

typedef struct		s_camera
{
	t_point		origin;
	t_vector	direction;
	int			fov;
	uint8_t		pad_[4];
}					t_camera;

typedef struct		s_light
{
	t_point		position;
	t_rgb		color;
}					t_light;

/*
** scene objects: wrapper struct, then sphere, plane, etc.
*/

typedef struct		s_obj_wrapper
{
	void		*obj;
	t_rgb		color;
	uint8_t		type;
	uint8_t		pad_[7];
}					t_obj_wrapper;

typedef struct		s_sphere
{
	t_point		centre;
	double		radius;
	t_vector	centre_rayorigin;
	double		c;
	t_bool		surface_side;
	uint8_t		pad_[7];
}					t_sphere;

typedef struct		s_plane
{
	t_point		position;
	t_vector	normal;
	double		n_dot_op;
}					t_plane;

typedef struct		s_triangle
{
	t_point		vertex1;
	t_point		vertex2;
	t_point		vertex3;
	t_vector	edge1;
	t_vector	edge2;
	t_vector	edge3;
	t_vector	normal;
	t_plane		plane;
}					t_triangle;

typedef struct		s_square
{
	t_point		centre;
	t_vector	normal;
	double		side_len;
	t_triangle	triangle1;
	t_triangle	triangle2;
}					t_square;

typedef struct		s_cylinder
{
	t_point		axis_middle;
	t_vector	axis_direction;
	double		radius;
	double		height;
	t_vector	rayorigin_middle;
	t_vector	ad_cross_oam;
	double		c;
	t_vector	axismiddle_intersectionpoint;
	double		distance_on_the_axis;
	t_bool		surface_side;
	uint8_t		pad_[7];
}					t_cylinder;

/*
** minilibx image data
*/

typedef struct		s_mlx_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	uint8_t	pad_[4];
}					t_mlx_image;

/*
** global struct for all the data
*/

typedef struct		s_global
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
}					t_global;

#endif
