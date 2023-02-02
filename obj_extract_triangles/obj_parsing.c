#include "obj_extract_triangles.h"

t_bool	obj_parse_tr_vertices(const char *line, t_tr_vertices *tr_vertices)
{
	line = parse_int(line + 2, &(tr_vertices->vertex1));
	if (line == NULL)
		return (FAILURE);
	while (*line != ' ')
		line++;
	line = parse_int(line + 1, &(tr_vertices->vertex2));
	if (line == NULL)
		return (FAILURE);
	while (*line != ' ')
		line++;
	line = parse_int(line + 1, &(tr_vertices->vertex3));
	if (line == NULL)
		return (FAILURE);
	return (SUCCESS);
}

void	obj_parse_triangles(t_obj_data *obj_data)
{
	t_list	*triangles_lines_iter;
	size_t	i;

	obj_data->triangles = (t_tr_vertices *)malloc(sizeof(t_tr_vertices) *
			obj_data->nb_triangles);
	if (obj_data->triangles == NULL)
	{
		perror("malloc (t_tr_vertices *)");
		return ;
	}
	ft_bzero(obj_data->triangles, sizeof(t_tr_vertices) * obj_data->nb_triangles);
	triangles_lines_iter = obj_data->triangles_lines;
	i = 0;
	while (triangles_lines_iter != NULL)
	{
		if (obj_parse_tr_vertices(triangles_lines_iter->content,
					obj_data->triangles + i) == FAILURE)
		{
			ft_putstr_fd("atoi vertex number", STDERR_FILENO);
			return ;
		}
		triangles_lines_iter = triangles_lines_iter->next;
		i++;
	}
	ft_lstclear(&(obj_data->triangles_lines), &free_list_elem);
}

void	replace_spaces_by_commas(char *str)
{
	while (*str != '\0')
	{
		if (*str == ' ')
			*str = ',';
		str++;
	}
}

t_bool	obj_parse_vertex(const char *line, char **vertex)
{
	size_t	line_len;

	errno = 0;
	line_len = ft_strlen(line);
	*vertex = (char *)malloc(sizeof(char) * (line_len - 2 + 1));
	if (*vertex == NULL)
		return (FAILURE);
	ft_strlcpy(*vertex, line + 2, line_len - 2 + 1);
	replace_spaces_by_commas(*vertex);
	return (SUCCESS);
}

void	obj_parse_vertices(t_obj_data *obj_data)
{
	t_list	*vertices_lines_iter;
	size_t	i;

	obj_data->vertices = (char **)malloc(sizeof(char *) *
			obj_data->nb_vertices);
	if (obj_data->vertices == NULL)
	{
		perror("malloc (char **)");
		return ;
	}
	ft_bzero(obj_data->vertices, sizeof(char *) * obj_data->nb_vertices);
	vertices_lines_iter = obj_data->vertices_lines;
	i = 0;
	while (vertices_lines_iter != NULL)
	{
		if (obj_parse_vertex(vertices_lines_iter->content,
					obj_data->vertices + i) == FAILURE)
		{
			perror("malloc (char *)");
			return ;
		}
		vertices_lines_iter = vertices_lines_iter->next;
		i++;
	}
	ft_lstclear(&(obj_data->vertices_lines), &free_list_elem);
}

void	obj_save_line(char *line, t_obj_data *obj_data)
{
	errno = 0;
	if (ft_memcmp(line, "v ", 2) == 0)
	{
		obj_data->nb_vertices++;
		if (add_to_list((void *)line, &(obj_data->vertices_lines)) == FAILURE)
		{
			perror("malloc (t_list)");
			return ;
		}
	}
	else if (ft_memcmp(line, "f ", 2) == 0)
	{
		obj_data->nb_triangles++;
		if (add_to_list((void *)line, &(obj_data->triangles_lines)) == FAILURE)
		{
			perror("malloc (t_list)");
			return ;
		}
	}
	else
		free(line);
}

void	obj_get_elements_from_file(int fd, t_obj_data *obj_data)
{
	char	*line;
	int8_t	ret;

	ret = 1;
	while (ret == 1)
	{
		errno = 0;
		ret = (int8_t)get_next_line(fd, &line);
		if (ret == ERROR)
		{
			perror("gnl");
			return ;
		}
		obj_save_line(line, obj_data);
	}
}
