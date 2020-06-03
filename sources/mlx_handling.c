#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>
#include <errno.h>

void	image_pixel_put(t_image *image, int x, int y, unsigned color)
{
	char		*pixel_pos;

	pixel_pos = image->addr + (y * image->line_len + x * (image->bits_per_pixel / 8));
	if (image->endian == 0)//LITTLE_ENDIAN
	{
		*pixel_pos = (char)color;
		if (image->bits_per_pixel >= 16)
			*(pixel_pos + 1) = (char)(color >> 8);
		if (image->bits_per_pixel >= 24)
			*(pixel_pos + 2) = (char)(color >> 16);
		if (image->bits_per_pixel >= 32)
			*(pixel_pos + 3) = (char)(color >> 24);
	}
	else if (image->endian == 1) //BIG_ENDIAN
	{
		if (image->bits_per_pixel >= 32)
		{
			*(pixel_pos + 3) = (char)color;
			*(pixel_pos + 2) = (char)(color >> 8);
			*(pixel_pos + 1) = (char)(color >> 16);
			*pixel_pos = (char)(color >> 24);
		}
		else if (image->bits_per_pixel >= 24)
		{
			*(pixel_pos + 2) = (char)color;
			*(pixel_pos + 1) = (char)(color >> 8);
			*pixel_pos = (char)(color >> 16);
		}
		else if (image->bits_per_pixel >= 16)
		{
			*(pixel_pos + 1) = (char)color;
			*pixel_pos = (char)(color >> 8);
		}
		else if (image->bits_per_pixel >= 8)
			*pixel_pos = (char)color;
	}
}

void	switch_camera(t_global *data, int8_t order)
{
	static t_image	*cur_image = NULL;
	t_image			*next_image;
	t_list			*images_iter;

	images_iter = data->images;
	if (cur_image == NULL)
		cur_image = ((t_image *)images_iter->content);
	next_image = cur_image;
	while (images_iter != NULL && images_iter->next != NULL)
	{
		if (order == 1 && ((t_image *)images_iter->content) == cur_image)
		{
			next_image = ((t_image *)images_iter->next->content);
			break ;
		}
		else if (order == -1 && ((t_image *)images_iter->next->content) == cur_image)
		{
			next_image = ((t_image *)images_iter->content);
			break ;
		}
		images_iter = images_iter->next;
	}
	if (next_image != cur_image)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, next_image->ptr, 0, 0);
		cur_image = next_image;
	}
}

void	quit_program(t_global *data)
{
	t_list			*images_iter;

	images_iter = data->images;
	while (images_iter != NULL)
	{
		mlx_destroy_image(data->mlx_ptr, ((t_image *)images_iter->content)->ptr);// err?
		images_iter = images_iter->next;
	}
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_data(data);
	exit(EXIT_SUCCESS);
}

int		key_hooks(int keycode, t_global *data)
{
	if (keycode == KEYCODE_ESCAPE)// define codes
		quit_program(data);
	else if (keycode == KEYCODE_RIGHT_ARROW)
		switch_camera(data, 1);
	else if (keycode == KEYCODE_LEFT_ARROW)
		switch_camera(data, -1);
	return (SUCCESS);
}

t_image	*new_image(t_global *data)
{
	t_image	*new_image;

	errno = 0;
	new_image = (t_image *)malloc(sizeof(t_image));
	if (new_image == NULL)
		return (NULL);// error
	errno = 0;
	if (add_to_list(new_image, &(data->images)) == FAILURE)
		return (NULL);// error
	new_image->ptr = mlx_new_image(data->mlx_ptr, data->res[0], data->res[1]);
	if (new_image->ptr == NULL)
	{
		free_data(data);
		error(MLX_NEW_IMAGE_ERROR);// free mlx_init
	}
	new_image->addr = mlx_get_data_addr(new_image->ptr,
		&(new_image->bits_per_pixel), &(new_image->line_len), &(new_image->endian));
	return (new_image);
}

void	check_resolution(t_global *data)
{
	int		screen_width;
	int		screen_height;

	errno = 0;
	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	if (screen_width <= 0 || screen_height <= 0)
		error(MLX_SCREEN_SIZE_ERROR);
	if (data->res[0] == 0 || data->res[0] > (size_t)screen_width)
		data->res[0] = (size_t)screen_width;
	if (data->res[1] == 0 || data->res[1] > (size_t)screen_height)
		data->res[1] = (size_t)screen_height;
}
