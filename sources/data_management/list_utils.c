/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:53 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 21:18:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_management.h"

t_bool	add_to_list(void *content, t_list **lst)
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
