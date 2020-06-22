/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:41:45 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:41:46 by mvidal-a         ###   ########.fr       */
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
	line = parse_coord(line, v);
	if (line == NULL)
		return (NULL);
	if (v->x > 1 || v->x < -1 ||
		v->y > 1 || v->y < -1 ||
		v->z > 1 || v->z < -1)
		return (NULL);
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
