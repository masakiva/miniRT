/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:52:05 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 12:03:36 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

# include "minirt.h"

double		sq(double n);
t_vector	add_vec(t_vector v1, t_vector v2);
t_vector	sub_vec(t_vector v1, t_vector v2);
t_vector	mult_vec_f(t_vector v1, double f);
t_vector	mult_vec_vec(t_vector v1, t_vector v2);
t_vector	div_vec(t_vector v1, double f);
t_vector	neg_vec(t_vector v1);
double		dot_vec(t_vector v1, t_vector v2);
t_vector	cross_vec(t_vector v1, t_vector v2);
double		length_squared_vec(t_vector v);
double		length_vec(t_vector v);
t_vector	unit_vec(t_vector v, double v_length);
void print_vec(t_vector v);

#endif
