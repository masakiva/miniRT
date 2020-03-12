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
#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>

int		g_errno = 0;

int8_t	check_name(char *name)
{
	if (ft_memcmp(name + ft_strlen(name) - 3, ".rt", 3) != 0)
		return (FALSE);
	return (TRUE);
}

void	parse_line(char *line, t_global *data)
{
	static char		*str_type[NB_TYPES] = {SPH, PLA, SQU, CYL,
		TRI, CAM, LIG, RES, AMB};
	static t_parse	types[NB_TYPES] = {p_sphere, p_plane, p_square, p_cylinder,
		p_triangle, p_camera, p_light, p_resolution, p_ambient_lightning};
	uint8_t			i;
	uint8_t			size;

	i = 0;
	while (i < NB_TYPES)
	{
		size = i < 5 ? 2 : 1;
		if (ft_memcmp(line, str_type[i], size) == 0)
		{
			types[i](line + size, data);
			return ;
		}
		i++;
	}
	//printf("LINE ERROR\n");
}

void		init_global_data(t_global **data)
{
	*data = (t_global *)malloc(sizeof(t_global));
	(*data)->cameras = NULL;
	(*data)->lights = NULL;
	(*data)->objects = NULL;
}

t_global	*parse_rtfile(char *rtfile)
{
	int			fd;
	char		*line;
	int8_t		ret;
	t_global	*data;

	if (check_name(rtfile) == FALSE)
	{
		g_errno = 1;
		printf("google ERROR HANDLING");
		printf("Error\nBad filename\n");
	}
	fd = open(rtfile, O_RDONLY);
	if (fd == ERROR)
		perror("open");
	ret = 1;
	data = NULL;
	if (fd != ERROR)
	{
		init_global_data(&data);
		while (ret == 1)
		{
			ret = get_next_line(fd, &line);
			if (ret != ERROR)
				parse_line(line, data);
			else
				printf("GNL ERROR\n");
			free(line);
		}
		close(fd);
	}
	return (data);
}

void	draw_window(t_global *data)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int 	i;
	int		j;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data->res[0], data->res[1], "miniRT");
	i = 0;
	while (i < data->res[0])
	{
		j = 400;
		while (j < 410)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, *((unsigned *)(data->color)));
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
}

#include "ft_printbits.h"

int		main(int argc, char **argv)
{
	t_global	*data;

	if (argc != 2)
		return (EXIT_FAILURE);
	data = parse_rtfile(argv[1]);
	if (data == NULL)
		return (EXIT_FAILURE);
	draw_window(data);
	//printf("%i data->cameras->content->fov\n", ((t_camera *)data->cameras->content)->fov);
	return (EXIT_SUCCESS);
}
