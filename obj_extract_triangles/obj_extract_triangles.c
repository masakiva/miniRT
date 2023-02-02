#include "obj_extract_triangles.h"

void	free_list_elem(void *content)
{
	free(content);
}

void	obj_free_data(t_obj_data *obj_data)
{
	size_t		i;

	ft_lstclear(&(obj_data->triangles_lines), &free_list_elem);
	i = 0;
	while (i < obj_data->nb_vertices)
	{
		free(obj_data->vertices[i]);
		i++;
	}
	free(obj_data->vertices);
	free(obj_data->triangles);
}

void	fill_triangles_rtfile(int fd, t_obj_data *obj_data)
{
	size_t	i;

	i = 0;
	while (i < obj_data->nb_triangles)
	{
		ft_putstr_fd("tr\t", fd);
		ft_putstr_fd(obj_data->vertices[obj_data->triangles[i].vertex1 - 1], fd);
		ft_putchar_fd('\t', fd);
		ft_putstr_fd(obj_data->vertices[obj_data->triangles[i].vertex2 - 1], fd);
		ft_putchar_fd('\t', fd);
		ft_putstr_fd(obj_data->vertices[obj_data->triangles[i].vertex3 - 1], fd);
		ft_putstr_fd("\t255,255,255\n", fd);
		i++;
	}
}

int		main(int argc, char **argv)
{
	int			fd;
	t_obj_data	obj_data;

	if (argc != 2)
		return (EXIT_FAILURE);
	ft_bzero(&obj_data, sizeof(t_obj_data));
	fd = open(argv[1], O_RDONLY);
	if (fd == ERROR)
		return (EXIT_FAILURE);
	obj_get_elements_from_file(fd, &obj_data);
	close(fd);
	obj_parse_vertices(&obj_data);
	obj_parse_triangles(&obj_data);
	fd = open("result.rt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd != ERROR)
	{
		fill_triangles_rtfile(fd, &obj_data);
		close(fd);
	}
	obj_free_data(&obj_data);
	return (EXIT_SUCCESS);
}
