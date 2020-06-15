/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_32_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:42:24 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/01/04 17:44:07 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	print_32_bits(uint32_t b)
{
	uint8_t	i;
	uint8_t	j;
	t_byte	b_towrite;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 8)
		{
			b_towrite = (b >> (31 - (i * 8 + j))) % 2 + '0';
			write(STDOUT_FILENO, &b_towrite, 1);
			j++;
		}
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
