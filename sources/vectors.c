/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:49:31 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/10 20:04:42 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double		sq(double n)
{
	return (n * n);
}

double		length_sq(t_vector v)// to keep? same as dot(v, v)
{
	return (sq(v.x) + sq(v.y) + sq(v.z));
}

double		length(t_vector v)
{
	return (sqrt(length_sq(v)));
}

t_vector	add(t_vector v1, t_vector v2)// to keep?
{
	t_vector v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vector	sub(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vector	mult(t_vector v1, double f)// to keep?
{
	t_vector v2;

	v2.x = v1.x * f;
	v2.y = v1.y * f;
	v2.z = v1.z * f;
	return (v2);
}

t_vector	div(t_vector v1, double f)// to keep?
{
	t_vector v2;

	if (f == 0)
		return (NULL);
	v2.x = v1.x / f; // div by zero error
	v2.y = v1.y / f;
	v2.z = v1.z / f;
	return (v2);
}

t_vector	neg(t_vector v1)// to keep?
{
	t_vector v2;

	v2.x = v1.x * -1;
	v2.y = v1.y * -1;
	v2.z = v1.z * -1;
	return (v2);
}

t_vector	unit(t_vector v1)
{
	return (div(v1, length(v1)));// div by zero
}

double		dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.x = v1.y * v2.z - v1.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z;
	v3.z = v1.x * v2.y - v1.y * v2.x;
	return (v3);
}

void		print_vec(t_vector v)
{
	printf("(%9f, %9f, %9f)\n", v.x, v.y, v.z);
}
