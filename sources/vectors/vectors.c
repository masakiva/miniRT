/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:49:31 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:18:34 by mvidal-a         ###   ########.fr       */
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
