/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_wrap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:41:50 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 11:50:34 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

const char	*skip_spaces_tabs(const char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

const char	*skip_comma(const char *str)
{
	if (*str == ',')
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

t_rgb		*wrap_object(void *obj, t_list **lst, uint8_t type)
{
	t_obj_wrapper	*obj_wrapper;

	errno = 0;
	obj_wrapper = (t_obj_wrapper *)malloc(sizeof(t_obj_wrapper));
	if (obj_wrapper == NULL)
	{
		free(obj);
		return (NULL);
	}
	if (add_to_list(obj_wrapper, lst) == FAILURE)
	{
		free(obj);
		return (NULL);
	}
	obj_wrapper->type = type;
	obj_wrapper->obj = obj;
	return (&(obj_wrapper->color));
}
