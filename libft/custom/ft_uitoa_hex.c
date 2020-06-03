/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:26:00 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/30 15:56:17 by mvidal-a         ###   ########.fr       */
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
		un /= 16;
	}
	return (len);
}

char			*ft_uitoa_hex(unsigned un, char v)
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
			if (un % 16 > 9 && v == 'x')
				unstr[len--] = (char)(un % 16 + 87);
			else if (un % 16 > 9 && v == 'X')
				unstr[len--] = (char)(un % 16 + 55);
			else if (un % 16 <= 9)
				unstr[len--] = (char)(un % 16 + '0');
			un /= 16;
		}
	}
	return (unstr);
}
