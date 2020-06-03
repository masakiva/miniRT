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
#include <errno.h>

void	parse_line(const char *line, t_global *data, size_t line_nb)
{
	static char		*type_identifier[NB_ELEM] = {RES, AMB, CAM, LIG, SPH, PLA,
		SQU, CYL, TRI};
	static t_parse	parse_elem[NB_ELEM] = {p_resolution, p_ambient_lightning,
		p_camera, p_light, p_sphere, p_plane, p_square, p_cylinder, p_triangle};
	uint8_t			cur_elem_iter;
	uint8_t			identifier_size;

	line = skip_spaces_tabs(line);
	if (*line == '\0')
		return ;
	cur_elem_iter = 0;
	while (cur_elem_iter < NB_ELEM)
	{
		identifier_size = ft_strlen(type_identifier[cur_elem_iter]);
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
		parsing_error(line_nb, cur_elem_iter, data);
}

void	cycle_through_lines(t_global *data, int fd)
{
	char		*line;
	int8_t		ret;
	size_t		line_nb;

	line_nb = 0;
	ret = 1;
	while (ret == 1)
	{
		errno = 0;
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
		{
			free_data(data);
			error(GNL_ERROR);
		}
		line_nb++;
		parse_line((const char *)line, data, line_nb);
		free(line);
	}
}

void	free_list_elem(void *content)
{
	free(content);
}

void	free_object(void *content)
{
	free(((t_obj *)content)->obj);
	free_list_elem(content);
}

void	free_data(t_global *data)
{
	ft_lstclear(&(data->images), &free_list_elem);
	free(data->mlx_ptr);
	ft_lstclear(&(data->cameras), &free_list_elem);
	ft_lstclear(&(data->lights), &free_list_elem);
	ft_lstclear(&(data->objects), &free_object);
	free(data);
}

void		init_global_struct(t_global **data)
{
	errno = 0;
	*data = (t_global *)malloc(sizeof(t_global));
	if (*data == NULL)
		error(MALLOC_ERROR);
	else
		ft_bzero(*data, sizeof(t_global));
}

void	check_name(const char *name)
{
	if (ft_memcmp(name + ft_strlen(name) - 3, ".rt", 3) != 0)
		error(RTFILE_NAME_ERROR);
}

t_global	*parse_rtfile(const char *rtfile)
{
	int			fd;
	t_global	*data;

	check_name(rtfile);
	errno = 0;
	fd = open(rtfile, O_RDONLY);
	if (fd == ERROR)
		error(OPEN_ERROR);
	data = NULL;
	init_global_struct(&data);
	cycle_through_lines(data, fd);
	errno = 0;
	if (close(fd) == ERROR)
		error(CLOSE_ERROR);
	if (data->cameras == NULL)
		error(NO_CAMERA_ERROR);
	return (data);
}
