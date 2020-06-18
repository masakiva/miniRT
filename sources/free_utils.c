#include "minirt.h"

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
