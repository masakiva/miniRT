/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:21:10 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/03/02 16:26:43 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	parse_line(char *line, t_global *data)
{
	static char		*str_type[NB_ELEM] = {SPH, PLA, SQU, CYL,
		TRI, CAM, LIG, RES, AMB};
	static t_parse	types[NB_ELEM] = {p_sphere, p_plane, p_square, p_cylinder,
		p_triangle, p_camera, p_light, p_resolution, p_ambient_lightning};
	static size_t	line_nb = 0;
	uint8_t			i;
	uint8_t			size;

	line_nb++;
	line = skip_sp_ht(line);
	if (*line != '\0')
	{
		i = 0;
		while (i < NB_ELEM)
		{
			size = i < 5 ? 2 : 1;
			if (ft_memcmp(line, str_type[i], size) == 0)
			{
				line = types[i](line + size, data);
				if (line == NULL)
					parsing_errors(line_nb, i, data);
				break ;
			}
			i++;
		}
		line = skip_sp_ht(line);
		if (*line != '\0')
			parsing_errors(line_nb, i, data);
	}
}

void		init_global_data(t_global **data)
{
	*data = (t_global *)malloc(sizeof(t_global));
	if (*data != NULL)
	{
		(*data)->cameras = NULL;
		(*data)->lights = NULL;
		(*data)->objects = NULL;
	}
	else
		errors(&alloc_data);
}

void	check_name(char *name)
{
	if (ft_memcmp(name + ft_strlen(name) - 3, ".rt", 3) != 0)
		errors(&bad_name);
}

t_global	*parse_rtfile(char *rtfile)
{
	int			fd;
	char		*line;
	int8_t		ret;
	t_global	*data;

	check_name(rtfile);
	fd = open(rtfile, O_RDONLY);
	if (fd == ERROR)
		errors(&open_failed);
	data = NULL;
	init_global_data(&data);
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
			errors(&gnl_error);
		parse_line(line, data);
		free(line);
	}
	close(fd);
	//check_data(data);
	return (data);
}
