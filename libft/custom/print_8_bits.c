/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_8_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:40:52 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/01/04 17:43:58 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void    print_8_bits(t_byte b)
{
    t_byte z;
	
	z = 0b10000000;
    while (z > 0)
    {
        if (b & z)
			ft_putchar_fd('1', STDOUT_FILENO);
        else
			ft_putchar_fd('0', STDOUT_FILENO);
        z >>= 1;
    }
	ft_putchar_fd('\n', STDOUT_FILENO);
}
