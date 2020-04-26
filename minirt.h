/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:24:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/09 18:25:09 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define SUCCESS	0
# define TRUE	1
# define FALSE	0
# define ERROR	-1

# define X		0
# define Y		1

# define R		1
# define G		2
# define B		3

# define NB_ELEM	9

# define SPH	"sp"
# define PLA	"pl"
# define SQU	"sq"
# define CYL	"cy"
# define TRI	"tr"
# define CAM	"c"
# define LIG	"l"
# define RES	"R"
# define AMB	"A"

# define NB_OBJ	5

enum	e_objects
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE
};

# define E_SPH "Sphere parameters not valid. The following must be specified in order:\n"\
	"· x,y,z coordinates of the sphere center: 0.0,0.0,20.6\n"\
	"· the sphere diameter: 12.6\n"\
	"· R,G,B colors in range [0-255]: 10, 0, 255\n"
# define E_PLA
# define E_SQU
# define E_CYL
# define E_TRI
# define E_CAM
# define E_LIG
# define E_RES "Resolution must be defined using two positive integers."
# define E_AMB
# define E_ID "Line does not begin with a proper element type identifier."

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

typedef struct	s_ray
{
	t_point		origin;
	t_vector	direction;
}				t_ray;

typedef struct	s_camera
{
	t_point		origin;
	t_vector	direction;
	int			fov;
	uint8_t		pad[4];
}				t_camera;

typedef struct	s_light
{
	double		coord[3];
	double		brightness;
	uint8_t		color[4];
	uint8_t		pad[4];
}				t_light;

typedef struct	s_obj
{
	void		*obj;
	uint8_t		type;
	uint8_t		pad[7];
}				t_obj;

typedef struct	s_sphere
{
	t_point		centre;
	double		radius;
	uint8_t		color[4];
	uint8_t		pad[4];
}				t_sphere;

typedef struct	s_plane
{
	t_point		position;
	t_vector	normal;
	uint8_t		color[4];
	uint8_t		pad[4];
}				t_plane;

typedef struct	s_square
{
	double		coord[3];
	double		o_vec[3];
	double		height;
	uint8_t		color[4];
	uint8_t		pad[4];
}				t_square;

typedef struct	s_cylinder
{
	double		coord[3];
	double		o_vec[3];
	double		diameter;
	double		height;
	uint8_t		color[4];
	uint8_t		pad[4];
}				t_cylinder;

typedef struct	s_triangle
{
	double		coord1[3];
	double		coord2[3];
	double		coord3[3];
	uint8_t		color[4];
	uint8_t		pad[4];
}				t_triangle;

typedef struct	s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	uint8_t	pad[4];
}				t_image;

typedef struct	s_global
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	size_t		res[2];
	double		amb_light;
	uint8_t		color[4];
	uint8_t		pad[4];
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
}				t_global;

typedef char	*(*t_parse)(char *, t_global *);
typedef t_bool	(*t_intersect)(t_ray, void *);

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

t_global		*parse_rtfile(char *rtfile);
char			*p_sphere(char *line, t_global *data);
char			*p_plane(char *line, t_global *data);
char			*p_square(char *line, t_global *data);
char			*p_cylinder(char *line, t_global *data);
char			*p_triangle(char *line, t_global *data);
char			*p_camera(char *line, t_global *data);
char			*p_light(char *line, t_global *data);
char			*p_resolution(char *line, t_global *data);
char			*p_ambient_lightning(char *line, t_global *data);

char			*skip_sp_ht(char *str);
char			*skip_digits(char *str);
char			*skip_int(char *str);
double			add_decimal(double nb, char *str);
double			ft_atof(char *str);
char			*skip_float(char *str);
char			*skip_int_comma(char *str);
char			*skip_float_comma(char *str);
char			*parse_coord(char *line, double coord[3]); //tmp
char			*parse_vector(char *line, t_vector *v);
char			*parse_color(char *line, uint8_t color[4]);
char			*parse_o_vec(char *line, double o_vec[3]);
void			add_to_list(void *cur_object, t_list **lst);
void			wrap_object(void *cur_obj, t_list **lst, int8_t type);

void			errors(void (*err_func)(void));
void			arg_missing();
void			bad_name();
void			open_failed();
void			alloc_data();
void			gnl_error();
void			type_identifier();

#endif
