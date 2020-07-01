/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:07:24 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/22 17:38:46 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_export.h"

char	*get_bmpfile_name(char *basename)
{
	static int	index = 0;
	char		*index_str;
	char		*suffix;
	char		*bmpfile_name;

	errno = 0;
	if (index == 0)
		suffix = ft_strdup(".bmp");
	else
	{
		index_str = ft_itoa(index);
		if (index_str == NULL)
			return (NULL);
		errno = 0;
		suffix = ft_strjoin(index_str, ".bmp");
		free(index_str);
	}
	if (suffix == NULL)
		return (NULL);
	index++;
	errno = 0;
	bmpfile_name = ft_strjoin(basename, suffix);
	free(suffix);
	return (bmpfile_name);
}

int		create_bmpfile(const char *rtfile_name, t_global *data)
{
	int		fd;
	char	*basename;
	char	*bmpfile_name;

	basename = ft_strrchr(rtfile_name, '/') + 1;
	basename[ft_strlen(basename) - 3] = '\0';
	fd = ERROR;
	while (fd == ERROR)
	{
		bmpfile_name = get_bmpfile_name(basename);
		if (bmpfile_name == NULL)
		{
			free_data(data);
			error_and_exit(MALLOC_ERROR);
		}
		errno = 0;
		fd = open(bmpfile_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
		free(bmpfile_name);
		if (fd == ERROR && errno != EEXIST)
		{
			free_data(data);
			error_and_exit(OPEN_BMPFILE_ERROR);
		}
	}
	return (fd);
}

void	fill_bmp_header(char *file_data, size_t file_size, t_global *data)
{
	file_data[0x0] = 'B';
	file_data[0x1] = 'M';
	uint_to_str_little_endian((unsigned)file_size, file_data + 0x2);
	file_data[0xA] = BMP_METADATA_SIZE;
	uint_to_str_little_endian((unsigned)data->res[WIDTH], file_data + 0x12);
	uint_to_str_little_endian((unsigned)data->res[HEIGHT], file_data + 0x16);
	file_data[0xE] = BMP_INFOHEADER_SIZE;
	file_data[0x1A] = BMP_NB_COLOR_PLANES;
	file_data[0x1C] = BMP_BITS_PER_PIXEL;
}

char	*get_bmpfile_data(int fd, t_global *data, size_t *file_size)
{
	size_t	line_padding;
	char	*file_data;

	line_padding = 0;
	if ((data->res[WIDTH] * 3) % 4 != 0)
		line_padding = 4 - (data->res[WIDTH] * 3) % 4;
	*file_size = BMP_METADATA_SIZE +
		(data->res[WIDTH] * 3 + line_padding) * data->res[HEIGHT];
	errno = 0;
	file_data = (char *)malloc(*file_size * sizeof(char));
	if (file_data == NULL)
	{
		free_data(data);
		close(fd);
		error_and_exit(MALLOC_ERROR);
	}
	ft_bzero(file_data, *file_size);
	fill_bmp_header(file_data, *file_size, data);
	if (data->cameras->next != NULL)
		ft_putstr_fd("Warning\nThe exported scene will be rendered from the "\
				"first camera's point of view.\n", STDERR_FILENO);
	fill_bmp_data(data, file_data + BMP_METADATA_SIZE, line_padding);
	return (file_data);
}

void	export_in_bmp(t_global *data, const char *rtfile_name)
{
	int		fd;
	size_t	file_size;
	ssize_t	bytes_written;

	if (data->res[WIDTH] == 0)
	{
		free_data(data);
		error_and_exit(RESOLUTION_MISSING_ERROR);
	}
	fd = create_bmpfile(rtfile_name, data);
	data->bmpfile_data = get_bmpfile_data(fd, data, &file_size);
	errno = 0;
	bytes_written = write(fd, data->bmpfile_data, file_size);
	free_data(data);
	if (bytes_written == ERROR)
	{
		close(fd);
		error_and_exit(WRITE_BMPFILE_ERROR);
	}
	else if (bytes_written < (ssize_t)file_size)
		write_error(bytes_written, file_size);
	errno = 0;
	if (close(fd) == ERROR)
		error_and_exit(CLOSE_BMPFILE_ERROR);
}
