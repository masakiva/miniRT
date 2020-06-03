/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:24:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/09 18:25:09 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SUCCESS	1
# define FAILURE	0
# define TRUE	1
# define FALSE	0
# define ERROR	-1

# define LITTLE_ENDIAN 0
# define BIG_ENDIAN 1

# define KEYCODE_ESCAPE 65307
# define KEYCODE_RIGHT_ARROW 65363
# define KEYCODE_LEFT_ARROW 65361

# define RES	"R"
# define AMB	"A"
# define CAM	"c"
# define LIG	"l"
# define SPH	"sp"
# define PLA	"pl"
# define SQU	"sq"
# define CYL	"cy"
# define TRI	"tr"
# define NB_ELEM	9

# define NB_OBJ	5

enum	e_object
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE
};

# include <stdint.h>
# include "libft.h"
#include <stdio.h>

typedef int8_t	t_bool;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef t_vector	t_point;
typedef t_vector	t_rgb;

typedef struct	s_ray
{
	t_point		origin;
	t_vector	direction;
}				t_ray;

typedef struct	s_intersection
{
	t_list		*obj;
	double		t;
}				t_intersection;

typedef struct	s_camera
{
	t_point		origin;
	t_vector	direction;// changer le nom : target
	int			fov;
	uint8_t		_pad[4];
}				t_camera;

typedef struct	s_light
{
	t_point		position;
	double		intensity;
	t_rgb		color;
}				t_light;

typedef struct	s_obj
{
	void		*obj;
	t_rgb		color;
	uint8_t		type;
	uint8_t		_pad[7];
}				t_obj;

typedef struct	s_sphere
{
	t_point		centre;
	double		radius;
}				t_sphere;

typedef struct	s_plane
{
	t_point		position;
	t_vector	normal;
}				t_plane;

typedef struct	s_square
{
	t_point		position;
	t_vector	normal;
	double		height;
}				t_square;

typedef struct	s_cylinder
{
	t_point		position;
	t_vector	normal;
	double		diameter;
	double		height;
}				t_cylinder;

typedef struct	s_triangle
{
	t_point		vertex1;
	t_point		vertex2;
	t_point		vertex3;
}				t_triangle;

typedef struct	s_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	uint8_t	_pad[4];
}				t_image;

typedef struct	s_global // couper en deux? mlx & scene
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_list		*images;

	size_t		res[2]; // ->resolution
	double		amb_light; // ->amb_light_intensity
	t_rgb		color; // ->amb_light_color
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
}				t_global;

# include "errors.h"

typedef const char	*(*t_parse)(const char *, t_global *);
typedef double		(*t_equations)(t_ray *, void *);
typedef t_vector	(*t_normal)(t_point, void *);

double			sq(double n);
t_vector		new_vector_default(void);
t_vector		new_vector(double x, double y, double z);
double			length_sq(t_vector v);
double			length(t_vector v);
t_vector		add(t_vector v1, t_vector v2);
t_vector		sub(t_vector v1, t_vector v2);
t_vector		mult(t_vector v1, double f);
t_vector		divi(t_vector v1, double f);
t_vector		neg(t_vector v1);
t_vector		unit(t_vector v1); // length en para?
double			dot(t_vector v1, t_vector v2);
t_vector		cross(t_vector v1, t_vector v2);
void print_vec(t_vector v);

void			free_data(t_global *data);
t_global		*parse_rtfile(const char *rtfile);
const char		*p_sphere(const char *line, t_global *data);
const char		*p_plane(const char *line, t_global *data);
const char		*p_square(const char *line, t_global *data);
const char		*p_cylinder(const char *line, t_global *data);
const char		*p_triangle(const char *line, t_global *data);
const char		*p_camera(const char *line, t_global *data);
const char		*p_light(const char *line, t_global *data);
const char		*p_resolution(const char *line, t_global *data);
const char		*p_ambient_lightning(const char *line, t_global *data);

const char		*skip_spaces_tabs(const char *str);
const char		*skip_int(const char *str);
int8_t			atoi_sign(const char *str, int *nb);
double			atof_decimal_part(const char *str);
int8_t			atof_double(const char *str, double *nb_f);
const char		*skip_float(const char *str);
const char		*skip_comma(const char *str);
const char		*parse_int(const char *line, int *i);
const char		*parse_float(const char *line, double *f);
const char		*parse_coord(const char *line, t_point *v);
const char		*parse_color(const char *line, t_rgb *color);
t_bool			add_to_list(void *cur_object, t_list **lst);
t_rgb			*wrap_object(void *cur_obj, t_list **lst, int8_t type);

void			image_pixel_put(t_image *image, int x, int y, unsigned color);
int				key_hooks(int keycode, t_global *data);
t_image			*new_image(t_global *data);
t_bool			draw_images(t_global *data);
void			check_resolution(t_global *data);
void			fill_image(t_global *data, t_image *cur_image, t_camera *cur_camera);

#endif
