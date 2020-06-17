/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:52:05 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:52:33 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

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
t_vector		unit(t_vector v1);
double			dot(t_vector v1, t_vector v2);
t_vector		cross(t_vector v1, t_vector v2);
void print_vec(t_vector v);

#endif
