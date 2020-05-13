#include "minirt.h"
#include <math.h>
#include <stdlib.h>

void            image_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}


double	i_sphere(t_ray *ray, void *obj)
{
	t_sphere	*sp;
	t_vector	OC;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t;

	sp = (t_sphere *)obj;
	OC = sub(ray->origin, sp->centre);
	//ray.direction = sub(ray.direction, ray.origin);
	a = length_sq(ray->direction);
	b = 2 * dot(ray->direction, OC);
	c = length_sq(OC) - sq(sp->radius);
	discriminant = sq(b) - 4 * a * c;
	if (discriminant < 0)
		t = 2147483647;
	else
		t = (-1 * b - sqrt(discriminant)) / (2 * a);
	return (t);
}

int		intersect(t_ray *ray, t_global *data)
{
	static t_intersect	types[1/*NB_OBJ*/] = {i_sphere/*, i_plane,
		i_square, i_cylinder, i_triangle*/};
	t_list			*cur_elem;
	double			t;
	double			t_cur;
	int				color;

	t = 2147483647;
	cur_elem = data->objects;
	while (cur_elem != NULL)
	{
		t_cur = types[((t_obj *)cur_elem->content)->type](ray, ((t_obj *)cur_elem->content)->obj);
		if(t_cur >= 0 && t_cur < t) // ou >= 1?
		{
			color = ((t_obj *)cur_elem->content)->color;
			t = t_cur;
		}
		cur_elem = cur_elem->next;
	}
	if (t == 2147483647)
		return (0x00000000);
	else
		return (color);
}

void	fill_image(t_global *data)
{
	size_t	x;
	size_t	y;
	size_t	view_width;
	size_t	view_height;
	double	half_width;
	double	half_height;
	double	pixel_size;
	int		color;
	t_ray	ray;

	ray.origin = ((t_camera *)data->cameras->content)->origin;
	ray.direction = ((t_camera *)data->cameras->content)->direction;
	view_width = data->res[0];
	view_height = data->res[1];

	half_width = tan((M_PI * ((t_camera *)data->cameras->content)->fov / 180) / 2);
	half_height = half_width * ((double)view_height / (double)view_width);
	pixel_size = half_width * 2 / (double)view_width;

	ray.direction.x += -1 * half_width + pixel_size / 2; // a retirer
	ray.direction.y += half_height - pixel_size / 2;
	printf("dir.x = %f, dir.y = %f (x = 0, y = 0)\n", ray.direction.x, ray.direction.y); // a retirer

	y = 0;
	while (y < view_height)
	{
		x = 0;
		while (x < view_width)
		{
			//ray.direction = unit(ray.direction); // pour les couleurs par rapport a la distance?
			color = intersect(&ray, data) * data->amb_light;
			image_pixel_put(&(data->img), x, y, color);
			ray.direction.x += pixel_size;
			x++;
		}
		ray.direction.y -= pixel_size;
		ray.direction.x -= half_width * 2;
		y++;
	}
	ray.direction.y += pixel_size; // a retirer
	printf("dir.x = %f, dir.y = %f (x = %zu, y = %zu)\n", ray.direction.x, ray.direction.y, x - 1, y - 1); // a retirer
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
