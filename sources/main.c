#include "minirt.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	check_rtfile_name(const char *file_name)
{
	if (ft_memcmp(file_name + ft_strlen(file_name) - 3, ".rt", 4) != 0)
		error(RTFILE_NAME_ERROR);
}

void	check_save_option(const char *option)
{
	if (ft_memcmp(option, "--save", 7) != 0)
		error(SAVE_OPTION_ERROR);
}

int		main(int argc, char **argv)
{
	t_global	*data;

	data = NULL;
	if (argc < 2 || argc > 3)
		error(ARGC_ERROR);
	else if (argc == 2)
	{
		check_rtfile_name(argv[1]);
		data = parse_rtfile(argv[1]);
		render_with_mlx(data);
	}
	else if (argc == 3)
	{
		check_rtfile_name(argv[1]);
		check_save_option(argv[2]);
		data = parse_rtfile(argv[1]);
		export_in_bmp(data, argv[1]);
		free_data(data);
	}
	return (EXIT_SUCCESS);
}
