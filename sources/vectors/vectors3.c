/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:17:53 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:17:54 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

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
