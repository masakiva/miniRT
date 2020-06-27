/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:49:31 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:41:01 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double		sq(double n)
{
	return (n * n);
}

t_vector	add_vec(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vector	sub_vec(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vector	mult_vec_f(t_vector v1, double f)
{
	t_vector v2;

	v2.x = v1.x * f;
	v2.y = v1.y * f;
	v2.z = v1.z * f;
	return (v2);
}

t_vector	mult_vec_vec(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.x = v1.x * v2.x;
	v3.y = v1.y * v2.y;
	v3.z = v1.z * v2.z;
	return (v3);
}

t_vector	div_vec(t_vector v1, double f)
{
	t_vector v2;

	v2.x = v1.x / f;
	v2.y = v1.y / f;
	v2.z = v1.z / f;
	return (v2);
}

t_vector	neg_vec(t_vector v)
{
	return (mult_vec_f(v, -1.0));
}

double		dot_vec(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x +
			v1.y * v2.y +
			v1.z * v2.z);
}

t_vector	cross_vec(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.x = v1.y * v2.z - v1.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z;
	v3.z = v1.x * v2.y - v1.y * v2.x;
	return (v3);
}

double		length_squared_vec(t_vector v)
{
	return (dot_vec(v, v));
}

double		length_vec(t_vector v)
{
	return (sqrt(length_squared_vec(v)));
}

t_vector	unit_vec(t_vector v, double v_length)
{
	return (div_vec(v, v_length));
}

void		print_vec(t_vector v)
{
	printf("(%9f, %9f, %9f)\n", v.x, v.y, v.z);
}
