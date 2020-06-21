/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:21:10 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:05:14 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_line(const char *line, t_global *data, size_t line_nb)
{
	static char		*type_identifier[NB_ELEM] = {RES, AMB, CAM, LIG, SPH, PLA,
		SQU, CYL, TRI};
	static t_parse	parse_elem[NB_ELEM] = {p_resolution, p_ambient_lighting,
		p_camera, p_light, p_sphere, p_plane, p_square, p_cylinder, p_triangle};
	uint8_t			cur_elem_iter;
	uint8_t			identifier_size;

	line = skip_spaces_tabs(line);
	if (*line == '\0' || *line == '#')
		return ;
	cur_elem_iter = 0;
	while (cur_elem_iter < NB_ELEM)
	{
		identifier_size = (uint8_t)ft_strlen(type_identifier[cur_elem_iter]);
		if (ft_memcmp(line, type_identifier[cur_elem_iter], identifier_size) == 0)
		{
			line = parse_elem[cur_elem_iter](line + identifier_size, data);
			break ;
		}
		cur_elem_iter++;
	}
	if (line != NULL)
		line = skip_spaces_tabs(line);
	if (line == NULL || *line != '\0')
		parsing_error_exit(line_nb, cur_elem_iter, data);
}

void	cycle_through_lines_and_parse(t_global *data, int fd)
{
	char		*line;
	int8_t		ret;
	size_t		line_nb;

	line_nb = 0;
	ret = 1;
	while (ret == 1)
	{
		errno = 0;
		ret = (int8_t)get_next_line(fd, &line);
		if (ret == ERROR)
		{
			free_data(data);
			close(fd);
			error_and_exit(GNL_ERROR);
		}
		line_nb++;
		parse_line((const char *)line, data, line_nb);
		free(line);
	}
}

void		init_global_struct(t_global **data, int fd)
{
	errno = 0;
	*data = (t_global *)malloc(sizeof(t_global));
	if (*data == NULL)
	{
		close(fd);
		error_and_exit(MALLOC_ERROR);
	}
	else
		ft_bzero(*data, sizeof(t_global));
}

t_global	*parse_rtfile(const char *rtfile)
{
	int			fd;
	t_global	*data;

	errno = 0;
	fd = open(rtfile, O_RDONLY);
	if (fd == ERROR)
		error_and_exit(OPEN_RTFILE_ERROR);
	data = NULL;
	init_global_struct(&data, fd);
	cycle_through_lines_and_parse(data, fd);
	errno = 0;
	if (close(fd) == ERROR)
	{
		free_data(data);
		error_and_exit(CLOSE_RTFILE_ERROR);
	}
	if (data->cameras == NULL)
	{
		free_data(data);
		error_and_exit(NO_CAMERA_ERROR);
	}
	return (data);
}
