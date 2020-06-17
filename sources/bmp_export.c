/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:07:24 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:27:42 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	uint_to_str_little_endian(unsigned nb, char *str)
{
	str[0] = (char)nb;
	str[1] = (char)(nb >> 8);
	str[2] = (char)(nb >> 16);
	str[3] = (char)(nb >> 24);
}

char	*get_bmpfile_name(char *basename, int index)
{
	char	*index_str;
	char	*suffix;
	char	*bmpfile_name;

	errno = 0;
	if (index == 0)
		suffix = ft_strdup(".bmp");
	else
	{
		index_str = ft_itoa(index);
		if (index_str == NULL)
			error(MALLOC_ERROR); // new code
		errno = 0;
		suffix = ft_strjoin(index_str, ".bmp");
		free(index_str);
	}
	if (suffix == NULL)
		error(MALLOC_ERROR); // new code
	errno = 0;
	bmpfile_name = ft_strjoin(basename, suffix);
	free(suffix);
	if (bmpfile_name == NULL)
		error(MALLOC_ERROR); // new code
	return (bmpfile_name);
}

int		create_bmpfile(const char *rtfile_name, t_global *data)
{
	int		fd;
	char	*basename;
	char	*bmpfile_name;
	int		i;

	basename = ft_strrchr(rtfile_name, '/') + 1;
	basename[ft_strlen(basename) - 3] = '\0';
	fd = ERROR;
	i = 0;
	while (fd == ERROR)
	{
		bmpfile_name = get_bmpfile_name(basename, i);
		fd = open(bmpfile_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
		free(bmpfile_name);
		if (fd == ERROR && errno != EEXIST)
		{
			free_data(data);
			error(OPEN_ERROR); // another code
		}
		i++;
	}
	return (fd);
}

void	fill_bmp_header(char *file_data, size_t file_size, t_global *data)
{
	file_data[0x0] = 'B';
	file_data[0x1] = 'M';
	uint_to_str_little_endian((unsigned)file_size, file_data + 0x2);
	file_data[0xA] = BMP_METADATA_SIZE;
	uint_to_str_little_endian((unsigned)data->res[0], file_data + 0x12);
	uint_to_str_little_endian((unsigned)data->res[1], file_data + 0x16);
	file_data[0xE] = BMP_INFOHEADER_SIZE;
	file_data[0x1A] = BMP_NB_COLOR_PLANES;
	file_data[0x1C] = BMP_BITS_PER_PIXEL;
}

void	export_in_bmp(t_global *data, const char *rtfile_name)
{
	size_t	line_padding;
	size_t	file_size;
	char	*file_data;
	int		fd;

	if (data->res[0] == 0)
	{
		free_data(data);
		error(RESOLUTION_MISSING_ERROR);
	}
	fd = create_bmpfile(rtfile_name, data);
	return ;
	line_padding = 0;
	if ((data->res[0] * 3) % 4 != 0)
		line_padding = 4 - (data->res[0] * 3) % 4;
	file_size = BMP_METADATA_SIZE + (data->res[0] * 3 + line_padding) * data->res[1];
	errno = 0;
	file_data = (char *)malloc(file_size * sizeof(char));
	if (file_data == NULL)
	{
		free_data(data);
		close(fd);
		error(MALLOC_ERROR); // another code?
	}
	ft_bzero(file_data, file_size);
	fill_bmp_header(file_data, file_size, data);

	size_t				x;
	size_t				y;
	int					color;
	t_ray				ray;
	t_view_properties	props;
	t_camera			*cur_camera;
	size_t				i;
	char				*data_addr;

	cur_camera = (t_camera *)data->cameras->content;
	get_view_properties(data, &props, cur_camera);
	ray.origin = cur_camera->origin;
	i = BMP_METADATA_SIZE;
	data_addr = file_data + i;
	y = 0;
	while (y < data->res[1])
	{
		i = (data->res[1] - y - 1) * (data->res[0] * 3 + line_padding);
		x = 0;
		while (x < data->res[0])
		{
			ray.direction = add(cur_camera->forward_vec,
						add(props.x_factor_vec, props.y_factor_vec));
			color = process_pixel(ray, data);
			data_addr[i] = color;
			data_addr[i + 1] = color >> 8;
			data_addr[i + 2] = color >> 16;
			next_pixel_x(cur_camera, &props);
			i += 3;
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
	printf("file_size = %zu\n", file_size);
	write(fd, file_data, file_size);
	close(fd);
	free(file_data);
}
