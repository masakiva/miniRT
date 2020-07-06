/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_derivates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:33:04 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:19:03 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
** atoi_sign return value depends on the beginning characters of str:
**		-1 if the number begins with '-' (negative or null number)
**		0 if the number does not begin with a digit (error)
**		1 otherwise (positive or null number)
*/

int8_t			atoi_sign(const char *str, int *nb)
{
	int8_t	sign_or_error;

	sign_or_error = 1;
	str = skip_spaces_tabs(str);
	if (*str == '-')
	{
		sign_or_error = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	*nb = 0;
	if (*str < '0' || *str > '9')
		sign_or_error = 0;
	while (*str >= '0' && *str <= '9')
	{
		*nb = *nb * 10 + *str - '0';
		str++;
	}
	*nb *= sign_or_error;
	return (sign_or_error);
}

static double	atof_decimal_part(const char *str)
{
	double	factor;
	double	decimal_part;

	if (*str != '.')
		return (0.0);
	else
		str++;
	decimal_part = 0.0;
	factor = 1.0;
	while (*str >= '0' && *str <= '9')
	{
		factor *= 10.0;
		if (*str != '0')
			decimal_part += (double)(*str - '0') / factor;
		str++;
	}
	return (decimal_part);
}

/*
** atof_double returns nonzero on success and 0 on error
*/

int8_t			atof_double(const char *str, double *nb_f)
{
	int		nb_i;
	int8_t	sign_or_error;

	nb_i = 0;
	sign_or_error = atoi_sign(str, &nb_i);
	*nb_f = (double)nb_i;
	if (sign_or_error == 1)
		*nb_f += atof_decimal_part(skip_int(str));
	else if (sign_or_error == -1)
		*nb_f -= atof_decimal_part(skip_int(str));
	return (sign_or_error);
}
