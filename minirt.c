#include "minirt.h"
#include <math.h>
#include <stdlib.h>

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

t_vector	n_sphere(t_point position, void *obj)
{
	t_sphere	*sp;
	t_vector	normal;

	sp = (t_sphere *)obj;
	normal = sub(position, sp->centre);
	normal = unit(normal);
	return (normal);
}

double	lighting(t_point cur_pos, t_list *elem, t_global *data)
{
	static t_normal	calc_normal[1/*NB_OBJ*/] = {n_sphere/*, n_plane,
		n_square, n_cylinder, n_triangle*/};
	t_vector		normal;
	double			intensity;
	t_list			*cur_light;
	t_vector		light_dir;
	double			n_dot_l;

	normal = calc_normal[((t_obj *)elem->content)->type](cur_pos, ((t_obj *)elem->content)->obj);
	intensity = 0.;
	cur_light = data->lights;
	while (cur_light != NULL)
	{
		light_dir = sub(((t_light *)cur_light->content)->position, cur_pos);
		n_dot_l = dot(normal, light_dir);
		if (n_dot_l > 0)
		{
			n_dot_l /= length(normal) * length(light_dir);
			intensity += ((t_light *)cur_light->content)->brightness * n_dot_l;// div by zero
		}
		cur_light = cur_light->next;
	}
	//printf("intensity %f\n", intensity);
	return (intensity);
}

int		rgb_fit_to_range(int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (value);
}

int		rgb_to_int(t_rgb color)
{
	int		ret;
	double	tmp;

	tmp = round(color.x);
	ret = rgb_fit_to_range((int)tmp);
	tmp = round(color.y);
	ret = (ret << 8) | rgb_fit_to_range((int)tmp);
	tmp = round(color.z);
	ret = (ret << 8) | rgb_fit_to_range((int)tmp);
	return (ret);
}

int		process_pixel(t_ray ray, t_global *data)// better name? previous: intersection
{
	static t_equations	find_t[1/*NB_OBJ*/] = {i_sphere/*, i_plane,
		i_square, i_cylinder, i_triangle*/};
	t_list			*cur_elem;
	double			closest_t;
	double			t_cur;
	t_list			*closest_elem;
	t_rgb			color;
	t_point			position;
	double			light;

	ray.direction = unit(ray.direction);
	closest_t = 2147483647;
	cur_elem = data->objects;
	while (cur_elem != NULL)
	{
		t_cur = find_t[((t_obj *)cur_elem->content)->type](&ray, ((t_obj *)cur_elem->content)->obj);
		if(t_cur >= 0 && t_cur < closest_t) // ou >= 1?
		{
			color = ((t_obj *)cur_elem->content)->color;
			closest_t = t_cur;
			closest_elem = cur_elem;
		}
		cur_elem = cur_elem->next;
	}
	if (closest_t == 2147483647)
		color = (t_rgb){0.0, 0.0, 0.0};
	else
	{
		position = add(ray.origin, mult(ray.direction, closest_t));
		light = lighting(position, closest_elem, data);
		color = mult(color, light + data->amb_light);
	}
	return (rgb_to_int(color));
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
	half_height = half_width * ((double)view_height / (double)view_width); // div by zero
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
			color = process_pixel(ray, data);
			image_pixel_put(data, x, y, color);
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
