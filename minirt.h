/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:20:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/10 16:39:51 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define TRUE	1
# define FALSE	0
# define ERROR	-1

//# define X		0
//# define Y		1
//
//# define R		1
//# define G		2
//# define B		3
//
//# define NB_TYPES	9
//
//# define SPH	"sp"
//# define PLA	"pl"
//# define SQU	"sq"
//# define CYL	"cy"
//# define TRI	"tr"
//# define CAM	"c"
//# define LIG	"l"
//# define RES	"R"
//# define AMB	"A"
//
//enum	e_types
//{
//	SPHERE,
//	PLANE,
//	SQUARE,
//	CYLINDER,
//	TRIANGLE
//};

# include <stdint.h>
#include <stdio.h>

# define RAY_T_MIN	0.0001
# define RAY_T_MAX	1.0e30

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef t_vector	t_point;

typedef struct	s_vector2
{
	double		x;
	double		y;
}				t_vector2;

typedef struct	s_ray
{
	t_point		origin;
	t_vector	direction;
	double		tmax;
}				t_ray;

typedef struct	s_intersection
{
	t_ray		r;
	double		t;
	void		*shape;
}				t_intersection;

typedef struct	s_plane
{
	t_point		position;
	t_vector	normal;

}				t_plane;

typedef struct	s_sphere
{
	t_point		centre;
	double		radius;
}				t_sphere;

typedef struct	s_persp_camera
{
	t_point		origin;
	t_vector	forward;
	t_vector	up;
	t_vector	right;
	double		h;
	double		w;
}				t_persp_camera;

typedef struct	s_image
{
	int		width;
	int		height;
	double	*data;
}				t_image;


double		sq(double n);
t_vector	new_vector_default(void);
t_vector	new_vector(double x, double y, double z);
double		length_sq(t_vector v);
double		length(t_vector v);
t_vector	add(t_vector v1, t_vector v2);
t_vector	sub(t_vector v1, t_vector v2);
t_vector	mul(t_vector v1, double f);
t_vector	div(t_vector v1, double f);
t_vector	neg(t_vector v1);
t_vector	normal(t_vector v1);
double		dot(t_vector v1, t_vector v2);
t_vector	cross(t_vector v1, t_vector v2);
void		print(t_vector v);



























#endif
