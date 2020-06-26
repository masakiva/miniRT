/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:41:45 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 11:44:59 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

const char	*parse_int(const char *line, int *i)
{
	if (atoi_sign(line, i) == 0)
		return (NULL);
	line = skip_float(line);
	return (line);
}

const char	*parse_float(const char *line, double *f)
{
	if (atof_double(line, f) == 0)
		return (NULL);
	line = skip_float(line);
	return (line);
}

const char	*parse_coord(const char *line, t_point *p)
{
	line = parse_float(line, &(p->x));
	if (line == NULL)
		return (NULL);
	line = skip_comma(line);
	line = parse_float(line, &(p->y));
	if (line == NULL)
		return (NULL);
	line = skip_comma(line);
	line = parse_float(line, &(p->z));
	return (line);
}

const char	*parse_unit_vector(const char *line, t_vector *v)
{
	double	vector_length;

	line = parse_coord(line, v);
	if (line == NULL)
		return (NULL);
	if (v->x == 0.0 && v->y == 0.0 && v->z == 0.0)
		return (NULL);
	if (v->x > 1.0 || v->x < -1.0 ||
		v->y > 1.0 || v->y < -1.0 ||
		v->z > 1.0 || v->z < -1.0)
		return (NULL);
	vector_length = length_vec(*v);
	if (vector_length != 1.0)
	{
		*v = unit_vec(*v, vector_length);
		ft_putstr_fd("Warning\nOne orientation vector has been normalised, "\
				"as it wasn't.\n", STDERR_FILENO);
	}
	return (line);
}

const char	*parse_color(const char *line, t_rgb *color)
{
	int		tmp;

	tmp = 0;
	line = parse_int(line, &tmp);
	if (line == NULL || tmp < 0 || tmp > 255)
		return (NULL);
	color->x = (double)tmp / 255;
	line = skip_comma(line);
	line = parse_int(line, &tmp);
	if (line == NULL || tmp < 0 || tmp > 255)
		return (NULL);
	color->y = (double)tmp / 255;
	line = skip_comma(line);
	line = parse_int(line, &tmp);
	if (line == NULL || tmp < 0 || tmp > 255)
		return (NULL);
	color->z = (double)tmp / 255;
	return (line);
}
