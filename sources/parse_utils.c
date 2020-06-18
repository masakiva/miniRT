/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:33:04 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/18 16:34:16 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>
#include <errno.h>

const char	*skip_spaces_tabs(const char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

const char	*skip_int(const char *str)
{
	str = skip_spaces_tabs(str);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	return (str);
}

const char	*skip_float(const char *str)
{
	str = skip_int(str);
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	return (str);
}

const char	*skip_comma(const char *str)
{
	if (*str == ',')
		str++;
	return (str);
}

/*
** atoi_sign return value depends on the beginning characters of str:
**		-1 if the number begins with '-' (negative or null number)
**		0 if the number does not begin with a digit (error)
**		1 otherwise (positive or null number)
*/

int8_t		atoi_sign(const char *str, int *nb)
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

double	atof_decimal_part(const char *str)
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

int8_t	atof_double(const char *str, double *nb_f)
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
	color->x = (double)tmp;
	line = skip_comma(line);
	line = parse_int(line, &tmp);
	if (line == NULL || tmp < 0 || tmp > 255)
		return (NULL);
	color->y = (double)tmp;
	line = skip_comma(line);
	line = parse_int(line, &tmp);
	if (line == NULL || tmp < 0 || tmp > 255)
		return (NULL);
	color->z = (double)tmp;
	return (line);
}

t_bool	add_to_list(void *content, t_list **lst)
{
	t_list		*new;

	errno = 0;
	new = ft_lstnew(content);
	if (new == NULL)
	{
		free(content);
		return (FAILURE);
	}
	ft_lstadd_back(lst, new);
	return (SUCCESS);
}

t_rgb	*wrap_object(void *cur_obj, t_list **lst, int8_t type)
{
	t_obj		*obj_wrapper;

	errno = 0;
	obj_wrapper = (t_obj *)malloc(sizeof(t_obj));
	if (obj_wrapper == NULL)
	{
		free(cur_obj);
		return (NULL);
	}
	if (add_to_list(obj_wrapper, lst) == FAILURE)
	{
		free(cur_obj);
		return (NULL);
	}
	obj_wrapper->type = type;
	obj_wrapper->obj = cur_obj;
	return (&(obj_wrapper->color));
}
