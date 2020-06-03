/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:10:47 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/01/30 12:20:50 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// return value: nonnegative on success (nb of chars written without the nl) and -1 + errno set on error
ssize_t	ft_putendl_fd(const char *s, int fd)
{
	ssize_t	ret;
	
	ret = ft_putstr_fd(s, fd);
	if (ret != -1)
	{
		if (ft_putchar_fd('\n', fd) == -1)
			ret = -1;
	}
	return (ret);
}
