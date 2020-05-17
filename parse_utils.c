/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:33:04 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/02 16:27:20 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

char	*skip_sp_ht(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

char	*skip_digits(char *str)
{
	while (*str >= '0' && *str <= '9')
		str++;
	return (str);
}

char	*skip_int(char *str)
{
	str = skip_sp_ht(str);
	if (*str == '-' || *str == '+')
		str++;
	str = skip_digits(str);
	return (str);
}

double	add_decimal(double nb, char *str)
{
	size_t	i;

	if (*str == '.')
		str++;
	i = 1;
	while (*str >= '0' && *str <= '9')
	{
		i *= 10;
		if (*str != '0') /// necessaire?
			nb += (double)(*str - '0') / i;
		str++;
	}
	return (nb);
}

double	ft_atof(char *str)
{
	int		nb_i;
	double	nb_f;

	nb_i = ft_atoi(str);
	nb_f = add_decimal((double)nb_i, skip_int(str));
	return (nb_f);
}

char	*skip_float(char *str)
{
	str = skip_int(str);
	if (*str == '.')
		str++;
	str = skip_digits(str);
	return (str);
}

char	*skip_int_comma(char *str)
{
	str = skip_int(str);
	if (*str == ',')
		str++;
	return (str);
}

char	*skip_float_comma(char *str)
{
	str = skip_float(str);
	if (*str == ',')
		str++;
	return (str);
}

char	*parse_int(char *line, int *i)
{
	*i = ft_atoi(line);
	line = skip_float(line);
	return (line);
}

char	*parse_float(char *line, double *f)
{
	*f = ft_atof(line);
	line = skip_float(line);
	return (line);
}

char	*parse_coord(char *line, double coord[3]) // temporaire
{
	int8_t	i;

	i = 0;
	while (i < 3)
	{
		coord[i] = ft_atof(line);
		line = skip_float_comma(line);
		i++;
	}
	return (line);
}

char	*parse_vector(char *line, t_vector *v)
{
	v->x = ft_atof(line);
	line = skip_float_comma(line);
	v->y = ft_atof(line);
	line = skip_float_comma(line);
	v->z = ft_atof(line);
	line = skip_float_comma(line);
	return (line);
}

char	*parse_color(char *line, t_rgb *color)
{
	color->x = (double)ft_atoi(line); // atoi renvoie 0 s'il n'y a pas de nombre...
	if (color->x < 0.0 || color->x > 255.0) return (NULL);
	line = skip_int_comma(line);
	color->y = (double)ft_atoi(line);
	if (color->y < 0.0 || color->y > 255.0) return (NULL);
	line = skip_int_comma(line);
	color->z = (double)ft_atoi(line);
	if (color->z < 0.0 || color->z > 255.0) return (NULL);
	line = skip_int_comma(line);
	return (line);
//	int8_t	i;
//	int		tmp;
//
//	*color = 0;
//	i = 2;
//	while (i >= 0)
//	{
//		tmp = ft_atoi(line);
//		if (tmp >= 0 && tmp <= 255)
//			*color |= tmp << 8 * i;
//		else
//			printf("COLOR NOT VALID\n");
//		line = skip_int_comma(line);
//		i--;
//	}
//	return (line);
}

char	*parse_o_vec(char *line, double o_vec[3])// temp
{
	int8_t	i;

	i = 0;
	while (i < 3)
	{
		o_vec[i] = ft_atof(line);
		if (o_vec[i] < -1 || o_vec[i] > 1)
			printf("3D ORIENTATION VECTOR NOT IN RANGE [-1,1]\n");
		line = skip_float_comma(line);
		i++;
	}
	return (line);
}

void	add_to_list(void *cur_obj, t_list **lst)
{
	t_list		*new;

	new = ft_lstnew(cur_obj);
	ft_lstadd_back(lst, new);
}

char	*wrap_object(void *cur_obj, t_list **lst, int8_t type, char *line)
{
	t_obj		*wrapper;

	wrapper = (t_obj *)malloc(sizeof(t_obj));
	//errr
	wrapper->type = type;
	wrapper->obj = cur_obj;
	line = parse_color(line, &(wrapper->color));
	//errr
	add_to_list(wrapper, lst);
	return (line);
}
