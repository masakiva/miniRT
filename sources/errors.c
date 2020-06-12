#include "minirt.h"
#include "errors.h"
#include "libft.h"
#include <stdlib.h>
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

void	error(t_error_code err_code)
{
	const char	*err_msg;

	err_msg = error_code_to_str(err_code);
	putstr_stderr("Error\n");
	if (err_code <= 3)
		putstr_stderr(err_msg);
	else
		perror(err_msg);
	exit(EXIT_FAILURE);
}

void	parsing_error(size_t line_nb, uint8_t type_index, t_global *data)
{
	static const char	*const err_msg[NB_ELEM + 1] = {E_RES, E_AMB, E_CAM,
		E_LIG, E_SPH, E_PLA, E_SQU, E_CYL, E_TRI, E_ID};

	free_data(data);
	if (errno != 0)
		error(MALLOC_ERROR);
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
