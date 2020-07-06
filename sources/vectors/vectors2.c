/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:17:58 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:17:59 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

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
