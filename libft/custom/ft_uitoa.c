/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:35:24 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/30 12:58:06 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	un_len(unsigned un)
{
	size_t	len;

	len = 0;
	if (un == 0)
		len++;
	while (un > 0)
	{
		len++;
		un /= 10;
	}
	return (len);
}

char			*ft_uitoa(unsigned un)
{
	char		*unstr;
	size_t		len;

	len = un_len(un);
	unstr = (char *)malloc(sizeof(char) * (len + 1));
	if (unstr != NULL)
	{
		unstr[len--] = '\0';
		if (un == 0)
			unstr[0] = '0';
		while (un > 0)
		{
			unstr[len--] = (char)(un % 10 + '0');
			un /= 10;
		}
	}
	return (unstr);
}
