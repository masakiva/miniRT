/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:01:09 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 14:14:06 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	putstr_stderr(const char *str)
{
	if (ft_putstr_fd(str, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write the error message on STDERR");
		exit(EXIT_FAILURE);
	}
}

const char	*error_code_to_str(t_error_code err_code)
{
	static const char *const err_str[NB_ERRORS] = {E0, E1, E2, E3, E4, E5, E6,
		E7, E8, E9, E10, E11, E12, E13, E14, E15};// voir const in next_minirt

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

void	write_error(ssize_t bytes_written, size_t file_size)
{
	ft_putstr_fd("Warning\nA problem occurred while writing in the .bmp file.\n"\
			"Only a number of ", STDERR_FILENO);
	ft_putnbr_fd((int)bytes_written, STDERR_FILENO);
	ft_putstr_fd(" bytes could be written in the file. Normally it should "\
			"have contained ", STDERR_FILENO);
	ft_putnbr_fd((int)file_size, STDERR_FILENO);
	ft_putstr_fd(" bytes.\n", STDERR_FILENO);
}

void	parsing_error_exit(size_t line_nb, uint8_t type_index, t_global *data)
{
	static const char	*const err_msg[NB_ELEM + 1] = {E_RES, E_AMB, E_CAM,
		E_LIG, E_SPH, E_PLA, E_TRI, E_SQU, E_CYL, E_ID};

	free_data(data);
	if (errno != 0)
		error_and_exit(MALLOC_ERROR);
	putstr_stderr("Error\n");
	putstr_stderr("In .rt file, line number ");
	if (ft_putnbr_fd((int)line_nb, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write the error message on STDERR");
		exit(EXIT_FAILURE);
	}
	putstr_stderr(": ");
	putstr_stderr(err_msg[type_index]);
	exit(EXIT_FAILURE);
}
