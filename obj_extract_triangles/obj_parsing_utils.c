#include "obj_extract_triangles.h"

t_bool		add_to_list(void *content, t_list **lst)
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

const char	*parse_int(const char *line, int *i)
{
	if (atoi_sign(line, i) == 0)
		return (NULL);
	line = skip_float(line);
	return (line);
}
