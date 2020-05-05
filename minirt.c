#include "minirt.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

void            image_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}


int		close_win(int keycode, t_global *data)
{
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(EXIT_SUCCESS);
	}
	return (TRUE);
}

t_bool	i_sphere(t_ray ray, void *obj)
{
	t_sphere	*sp;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	sp = (t_sphere *)obj;
	ray.origin = sub(ray.origin, sp->centre);
	a = length_sq(ray.direction);
	b = 2 * dot(ray.direction, ray.origin);
	c = length_sq(ray.origin) - sp->radius;
	discriminant = sq(b) - 4 * a * c;
	if (discriminant < 0)
		return (FALSE);
	return (TRUE);
}

t_bool	intersect(t_ray ray, t_global *data)
{
	static t_intersect	types[1/*NB_OBJ*/] = {i_sphere/*, i_plane,
		i_square, i_cylinder, i_triangle*/};
	t_list			*cur;

	cur = data->objects;
	while (cur != NULL)
	{
		if(types[((t_obj *)cur->content)->type](ray, ((t_obj *)cur->content)->obj) == TRUE)
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}

t_ray	calc_dir(t_ray ray, size_t x, size_t y, t_global *data)
{
	double	halfwidth;
	double	halfheight;
	double	x_mod;
	double	y_mod;

	halfwidth = tan((M_PI * ((t_camera *)data->cameras->content)->fov / 180) / 2);
	halfheight = halfwidth * (data->res[0] / data->res[1]);
	x_mod = 2 * x / data->res[0] - 1;
	y_mod = 2 * y / data->res[1] - 1;
	ray.direction.x += halfwidth * x_mod; //?
	ray.direction.y += halfheight * y_mod; //?
	ray.direction = unit(ray.direction); //?
	return (ray);
}

void	fill_image(t_global *data)
{
	size_t	x;
	size_t	y;
	size_t	width;
	size_t	height;
	t_ray	ray;

	ray.origin = ((t_camera *)data->cameras->content)->origin;
	ray.direction = ((t_camera *)data->cameras->content)->direction;
	width = data->res[0];
	height = data->res[1];
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (intersect(calc_dir(ray, x, y, data), data) == TRUE)
				image_pixel_put(&(data->img), x, y, 0x00FFFFFF);
			else
				image_pixel_put(&(data->img), x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

t_bool	draw_image(t_global *data)
{
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->res[0], data->res[1]);
	data->img.addr = mlx_get_data_addr(data->img.ptr,
			&(data->img.bpp), &(data->img.line_len), &(data->img.endian));
	fill_image(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (TRUE);
}

t_bool	draw_window(t_global *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FALSE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->res[0], data->res[1], "miniRT");
	draw_image(data);
	mlx_key_hook(data->win_ptr, &close_win, data);
	mlx_loop(data->mlx_ptr);
	return (TRUE);
}

int		main(int argc, char **argv)
{
	t_global	*data;
	t_bool		ret;

//	char	*line;
//	int		fd;
//	int		ret;

	if (argc != 2)
		return (EXIT_FAILURE);
	data = parse_rtfile(argv[1]);
	if (data == NULL)
		return (EXIT_FAILURE);
	ret = draw_window(data);
	if (ret == FALSE)
		return (EXIT_FAILURE);

//	fd = open(argv[1], O_RDONLY);
//	if (fd == ERROR)
//		errors(&open_failed);
//	ret = get_next_line(fd, &line);
//	if (ret == ERROR)
//		errors(&gnl_error);
//	printf("ret = %d\n", ret);
//	printf("line = %s\n", line);

	return (EXIT_SUCCESS);
}
