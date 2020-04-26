#include "minirt.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	putstr_stderr(char *str)
{
	if (ft_putstr_fd(str, STDERR_FILENO) == ERROR)
		perror("Cannot write on STDERR");
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
	perror("Cannot read file or allocate memory");
	free(data);
}

void	errors(void (*err_func)(void))
{
	if (ft_putstr_fd("Error\n", STDERR_FILENO) != ERROR)
		(*err_func)();
	else
		stderr_error();
	exit(EXIT_FAILURE);
}

void	parsing_errors(size_t line_nb, uint8_t type_index, t_global *data, uint8_t err_code)
{
	/*static*/ char	*err_msg[NB_ELEM + 1] = {E_SPH, E_PLA, E_SQU, E_CYL, E_TRI, E_CAM, E_LIG, E_RES, E_AMB, E_ID};
	/*static*/ char	*err_details[] = {E_O, E_OO};

if 	putstr_stderr("Error\n") == -1
	exit(EXIT_FAILURE);


	putstr_stderr("Line number ");
	if (ft_putnbr_fd(line_nb, STDERR_FILENO) == -1)
		stderr_error();
	putstr_stderr(": ");
	putstr_stderr(err_msg[type_index]);
	putstr_stderr("\n");
	putstr_stderr(err_details[err_code]);
	putstr_stderr("\n");
	free(data);
	exit(EXIT_FAILURE);
}
