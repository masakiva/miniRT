#ifndef OBJ_EXTRACT_TRIANGLES_H
# define OBJ_EXTRACT_TRIANGLES_H

#include "includes/parsing.h"

typedef struct	s_tr_vertices
{
	int		vertex1;
	int		vertex2;
	int		vertex3;
	char	pad_[4];
}				t_tr_vertices;

typedef struct	s_obj_data
{
	size_t			nb_vertices;
	size_t			nb_triangles;
	t_list			*vertices_lines;
	t_list			*triangles_lines;
	char			**vertices;
	t_tr_vertices	*triangles;
}				t_obj_data;

void	free_list_elem(void *content);

void	obj_get_elements_from_file(int fd, t_obj_data *obj_data);
void	obj_parse_vertices(t_obj_data *obj_data);
void	obj_parse_triangles(t_obj_data *obj_data);

#endif
