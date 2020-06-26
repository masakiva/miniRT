/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:39:59 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 11:33:58 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "mlx_handling.h"
#include "bmp_export.h"
#include "errors.h"

static void	check_rtfile_name(const char *file_name)
{
	if (ft_memcmp(file_name + ft_strlen(file_name) - 3, ".rt", 4) != 0)
		error_and_exit(RTFILE_NAME_ERROR);
}

static void	check_save_option(const char *option)
{
	if (ft_memcmp(option, "--save", 7) != 0)
		error_and_exit(SAVE_OPTION_ERROR);
}

int			main(int argc, char **argv)
{
	t_global	*data;

	data = NULL;
	if (argc < 2 || argc > 3)
		error_and_exit(ARGC_ERROR);
	else if (argc == 2)
	{
		check_rtfile_name(argv[1]);
		data = parse_rtfile(argv[1]);
		calc_scene_properties(data);
		render_with_mlx(data);
	}
	else if (argc == 3)
	{
		check_rtfile_name(argv[1]);
		check_save_option(argv[2]);
		data = parse_rtfile(argv[1]);
		calc_scene_properties(data);
		export_in_bmp(data, argv[1]);
	}
	return (EXIT_SUCCESS);
}
