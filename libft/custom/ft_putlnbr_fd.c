/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:42:38 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/30 11:51:28 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putlnbr_fd(long n, int fd)
{
	char	c;

//	if (n == -9223372036854775808)
//	{
//		write(fd, "-9223372036854775808", 20);
//		return ;
//	}
//	else
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
		ft_putlnbr_fd(n / 10, fd);
	c = n % 10 + 48;
	write(fd, &c, 1);
}
