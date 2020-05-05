#include "minirt.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	putstr_stderr(char *str)
{
	if (ft_putstr_fd(str, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write on STDERR");
		exit(EXIT_FAILURE);
	}
}

void	arg_missing()
{
	putstr_stderr("A scene description file with the .rt extension must be given as argument.\n");
}

void	bad_name()
{
	putstr_stderr("The name of the file given as argument must end with '.rt'.\n");
}

void	open_failed()
{
	perror("Cannot open file");
}

void	alloc_data()
{
	perror("Cannot allocate required memory");
}

void	gnl_error()
{
	//free(data);
	perror("Cannot read file or allocate memory");
}

void	errors(void (*err_func)(void))
{
	putstr_stderr("Error\n"); // no free if it fails
	(*err_func)();
	exit(EXIT_FAILURE);
}

void	parsing_errors(size_t line_nb, uint8_t type_index, t_global *data)
{
	/*static*/ char	*err_msg[NB_ELEM + 1] = {E_SPH, E_PLA, E_SQU, E_CYL, E_TRI, E_CAM, E_LIG, E_RES, E_AMB, E_ID};

	free(data);
	putstr_stderr("Error\n");
	putstr_stderr("Line number ");
	if (ft_putnbr_fd(line_nb, STDERR_FILENO) == ERROR)
	{
		perror("Cannot write on STDERR");
		exit(EXIT_FAILURE);
	}
	putstr_stderr(": ");
	putstr_stderr(err_msg[type_index]);
	exit(EXIT_FAILURE);
}
