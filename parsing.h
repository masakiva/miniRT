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

# define TRUE	1
# define FALSE	0
# define ERROR	-1

# define X		0
# define Y		1

# define R		1
# define G		2
# define B		3

# define NB_TYPES	9

# define SPH	"sp"
# define PLA	"pl"
# define SQU	"sq"
# define CYL	"cy"
# define TRI	"tr"
# define CAM	"c"
# define LIG	"l"
# define RES	"R"
# define AMB	"A"

enum	e_types
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

typedef struct	s_camera
{
	double		coord[3];
	double		o_vec[3];
	int			fov;
}				t_camera;

typedef struct	s_light
{
	double		coord[3];
	double		brightness;
	uint8_t		color[4];
}				t_light;

typedef struct	s_sphere
{
	uint8_t		type;
	double		coord[3];
	double		diameter;
	uint8_t		color[4];
}				t_sphere;

typedef struct	s_plane
{
	uint8_t		type;
	double		coord[3];
	double		o_vec[3];
	uint8_t		color[4];
}				t_plane;

typedef struct	s_square
{
	uint8_t		type;
	double		coord[3];
	double		o_vec[3];
	double		height;
	uint8_t		color[4];
}				t_square;

typedef struct	s_cylinder
{
	uint8_t		type;
	double		coord[3];
	double		o_vec[3];
	double		diameter;
	double		height;
	uint8_t		color[4];
}				t_cylinder;

typedef struct	s_triangle
{
	uint8_t		type;
	double		coord1[3];
	double		coord2[3];
	double		coord3[3];
	uint8_t		color[4];
}				t_triangle;

typedef struct	s_global
{
	int			res[2];
	double		amb_light;
	uint8_t		color[4];
	t_list		*cameras;
	t_list		*lights;
	t_list		*objects;
}				t_global;

typedef void	(*t_parse)(char *, t_global *);

void			p_sphere(char *line, t_global *data);
void			p_plane(char *line, t_global *data);
void			p_square(char *line, t_global *data);
void			p_cylinder(char *line, t_global *data);
void			p_triangle(char *line, t_global *data);
void			p_camera(char *line, t_global *data);
void			p_light(char *line, t_global *data);
void			p_resolution(char *line, t_global *data);
void			p_ambient_lightning(char *line, t_global *data);

char			*skip_sp_ht(char *str);
char			*skip_digits(char *str);
char			*skip_int(char *str);
double			add_decimal(double nb, char *str);
double			ft_atof(char *str);
char			*skip_float(char *str);
char			*skip_int_comma(char *str);
char			*skip_float_comma(char *str);
char			*parse_coord(char *line, double coord[3]);
char			*parse_color(char *line, uint8_t color[4]);
char			*parse_o_vec(char *line, double o_vec[3]);
void			add_to_list(void *cur_object, t_list **lst);

#endif
