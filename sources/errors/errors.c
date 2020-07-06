/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:01:09 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/06 22:44:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void		putstr_stderr(const char *str)
{
	if (ft_putstr_fd(str, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write the error message on STDERR");
		exit(EXIT_FAILURE);
	}
}

void		error_and_exit(t_error_code err_code)
{
	static const char *err_msg[NB_ERRORS] = {NULL, E1, E2, E3, E4, E5, E6, E7,
		E8, E9, E10, E11, E12, E13, E14, E15};

	putstr_stderr("Error\n");
	if (err_code == 0)
	{
		putstr_stderr(E0_1);
		putstr_stderr(E0_2);
		putstr_stderr(E0_3);
	}
	else if (err_code <= RESOLUTION_MISSING_ERROR)
		putstr_stderr(err_msg[err_code]);
	else
		perror(err_msg[err_code]);
	exit(EXIT_FAILURE);
}

void		write_error(ssize_t bytes_written, size_t file_size)
{
	ft_putstr_fd("Warning\nA problem occurred while writing the .bmp file.\n"\
			"Only a number of ", STDERR_FILENO);
	ft_putnbr_fd((int)bytes_written, STDERR_FILENO);
	ft_putstr_fd(" bytes could be written in the file. Normally it should "\
			"have contained ", STDERR_FILENO);
	ft_putnbr_fd((int)file_size, STDERR_FILENO);
	ft_putstr_fd(" bytes.\n", STDERR_FILENO);
}

static void	print_elem_err_msg(uint8_t type_index)
{
	if (type_index == 0 || type_index == 1)
		print_elem_err_msg1(type_index);
	else if (type_index == 2 || type_index == 3)
		print_elem_err_msg2(type_index);
	else if (type_index == 4 || type_index == 5)
		print_elem_err_msg3(type_index);
	else if (type_index == 6 || type_index == 7)
		print_elem_err_msg4(type_index);
	else if (type_index == 8 || type_index == 9)
		print_elem_err_msg5(type_index);
}

void		parsing_error_exit(size_t line_nb, uint8_t type_index, t_global *data)
{
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
	print_elem_err_msg(type_index);
	exit(EXIT_FAILURE);
}
