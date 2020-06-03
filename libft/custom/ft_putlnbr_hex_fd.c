/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_hex_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:40:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/30 11:51:44 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putlnbr_hex_fd(long n, char v, int fd)
{
	char	c;

//	if (n == -9223372036854775808)
//	{
//		write(fd, "-8000000000000000", 17);
//		return ;
//	}
//	else
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 15)
		ft_putlnbr_hex_fd(n / 16, v, fd);
	if (n % 16 > 9 && v == 'x')
		c = n % 16 + 87;
	else if (n % 16 > 9 && v == 'X')
		c = n % 16 + 55;
	else if (n % 16 <= 9)
		c = n % 16 + 48;
	write(fd, &c, 1);
}
