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

t_intersection	closest_intersection(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[1/*NB_OBJ*/] = {i_sphere/*, i_plane,
		i_square, i_cylinder, i_triangle*/};
	double			cur_t;
	t_list			*closest_elem;
	double			closest_t;

	closest_t = t_max;
	while (obj != NULL)
	{
		cur_t = find_t[((t_obj *)obj->content)->type](&ray, ((t_obj *)obj->content)->obj);
		if (cur_t >= t_min && cur_t < closest_t) // ou >= 1? ; et s'il y a deux memes t
		{
			closest_t = cur_t;
			closest_elem = obj;
		}
		obj = obj->next;
	}
	return ((t_intersection){closest_elem, closest_t});
}

t_bool	intersection_or_not(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[1/*NB_OBJ*/] = {i_sphere/*, i_plane,
		i_square, i_cylinder, i_triangle*/};
	double			cur_t;

	while (obj != NULL)
	{
		cur_t = find_t[((t_obj *)obj->content)->type](&ray, ((t_obj *)obj->content)->obj);
		if (cur_t >= t_min && cur_t < t_max) // ou >= 1? ; et s'il y a deux memes t
			return (TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

t_bool	shadows(t_point cur_pos, t_vector light_dir, t_list *objects)
{
	t_ray	light_ray;

	light_ray.origin = cur_pos;
	light_ray.direction = light_dir;
	if (intersection_or_not(light_ray, objects, 0.00001 /**/, 1) == TRUE)
		return (TRUE);
	else
		return (FALSE);
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
			if (shadows(cur_pos, light_dir, data->objects) == FALSE)
			{
				n_dot_l /= length(normal) * length(light_dir);
				intensity += ((t_light *)cur_light->content)->brightness * n_dot_l;// div by zero
			}
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
	t_rgb			color;
	t_point			position;
	double			light;
	t_intersection	intxn;

	//ray.direction = unit(ray.direction);
	intxn = closest_intersection(ray, data->objects, 0, 2147483647);
	if (intxn.t == 2147483647)
		color = (t_rgb){0.0, 0.0, 0.0};
	else
	{
		color = ((t_obj *)intxn.obj->content)->color;
		position = add(ray.origin, mult(ray.direction, intxn.t));
		light = lighting(position, intxn.obj, data);
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

	ray.direction.x += -1 * half_width + pixel_size / 2;
	ray.direction.y += 1 * half_height - pixel_size / 2;
	printf("dir.x = %f, dir.y = %f (x = 0, y = 0)\n", ray.direction.x, ray.direction.y);

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
	ray.direction.y += pixel_size; // pour le printf
	printf("dir.x = %f, dir.y = %f (x = %zu, y = %zu)\n", ray.direction.x, ray.direction.y, x - 1, y - 1);
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
