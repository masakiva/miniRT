#include "parsing.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	arg_missing()
{
	if (ft_putstr_fd("A scene description file with the .rt extension must be given as argument.\n", STDERR_FILENO) == -1)
		perror("Cannot write on STDERR");
}

void	bad_name()
{
	if (ft_putstr_fd("The name of the file given as argument must end with '.rt'.\n", STDERR_FILENO) == -1)
		perror("Cannot write on STDERR");
}

void	open_failed()
{
	perror("Cannot open file");
}

void	gnl_error()
{
	perror("Cannot read file or allocate memory");
}

void	errors(void (*err_func)(void))
{
	if (ft_putstr_fd("Error\n", STDERR_FILENO) != ERROR)
		(*err_func)();
	else
		perror("write");
	exit(EXIT_FAILURE);
}
