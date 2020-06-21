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

t_rgb	*wrap_object(void *cur_obj, t_list **lst, uint8_t type)
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
