/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:01:09 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:26:28 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h" // inverser: include errors.h ici, minirt.h dans errors.h
#include <stdlib.h> // ... et include les lib dans errors.h
#include <unistd.h>
#include <errno.h>

void	putstr_stderr(const char *str)
{
	if (ft_putstr_fd(str, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write on STDERR");
		exit(EXIT_FAILURE);
	}
}

const char	*error_code_to_str(t_error_code err_code)
{
	static const char *const err_str[NB_ERRORS] = {E0, E1, E2, E3, E4, E5, E6,
		E7, E8, E9, E10, E11};
	return (err_str[err_code]);
}

void	error_and_exit(t_error_code err_code)
{
	const char	*err_msg;

	err_msg = error_code_to_str(err_code);
	putstr_stderr("Error\n");
	if (err_code <= RESOLUTION_MISSING_ERROR)
		putstr_stderr(err_msg);
	else
		perror(err_msg);
	exit(EXIT_FAILURE);
}

void	parsing_error_exit(size_t line_nb, uint8_t type_index, t_global *data)
{
	static const char	*const err_msg[NB_ELEM + 1] = {E_RES, E_AMB, E_CAM,
		E_LIG, E_SPH, E_PLA, E_SQU, E_CYL, E_TRI, E_ID};

	free_data(data);
	if (errno != 0)
		error_and_exit(MALLOC_ERROR);
	putstr_stderr("Error\n");
	putstr_stderr("In .rt file, line number ");
	if (ft_putnbr_fd(line_nb, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write on STDERR");
		exit(EXIT_FAILURE);
	}
	putstr_stderr(": ");
	putstr_stderr(err_msg[type_index]);
	exit(EXIT_FAILURE);
}
