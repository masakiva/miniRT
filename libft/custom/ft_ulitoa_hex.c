/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:26:00 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/30 16:10:58 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	uln_len(unsigned long uln)
{
	size_t	len;

	len = 0;
	if (uln == 0)
		len++;
	while (uln > 0)
	{
		len++;
		uln /= 16;
	}
	return (len);
}

char			*ft_ulitoa_hex(unsigned long uln, char v)
{
	char		*ulnstr;
	size_t		len;

	len = uln_len(uln);
	ulnstr = (char *)malloc(sizeof(char) * (len + 1));
	if (ulnstr != NULL)
	{
		ulnstr[len--] = '\0';
		if (uln == 0)
			ulnstr[0] = '0';
		while (uln > 0)
		{
			if (uln % 16 > 9 && v == 'x')
				ulnstr[len--] = (char)(uln % 16 + 87);
			else if (uln % 16 > 9 && v == 'X')
				ulnstr[len--] = (char)(uln % 16 + 55);
			else if (uln % 16 <= 9)
				ulnstr[len--] = (char)(uln % 16 + '0');
			uln /= 16;
		}
	}
	return (ulnstr);
}
