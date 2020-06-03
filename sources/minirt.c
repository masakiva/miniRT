#include "minirt.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>

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
	if (discriminant < 0.0)
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

double	i_plane(t_ray *ray, void *obj)
{
	t_plane		*pl;
	double		d_dot_n;
	double		t;

	pl = (t_plane *)obj;
	d_dot_n = dot(ray->direction, pl->normal);
	if (d_dot_n == 0)
	{
		if (dot(sub(ray->origin, pl->position), pl->normal) == 0)
			t = 1; ///////////////////// arbitraire
		else
			t = 2147483647;
	}
	else
	{
		t = (1 / d_dot_n) *
			(dot(pl->position, pl->normal) - dot(ray->origin, pl->normal));
	}
	return (t);
}

t_vector	n_plane(t_point position, void *obj)
{
	(void)position;
	return (((t_plane *)obj)->normal);
}

t_intersection	closest_intersection(t_ray ray, t_list *obj, double t_min, double t_max)
{
	static t_equations	find_t[2/*NB_OBJ*/] = {i_sphere, i_plane/*,
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
	static t_equations	find_t[2/*NB_OBJ*/] = {i_sphere, i_plane/*,
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
	static t_normal	calc_normal[2/*NB_OBJ*/] = {n_sphere, n_plane/*,
		n_square, n_cylinder, n_triangle*/};
	t_vector		normal;
	double			intensity;
	t_light			*cur_light; // faire pareil pour les deux fonctions d'intersection?
	t_list			*lights_iter;
	t_vector		light_dir;
	double			n_dot_l;

	normal = calc_normal[((t_obj *)elem->content)->type](cur_pos, ((t_obj *)elem->content)->obj);
	intensity = 0.0;
	lights_iter = data->lights;
	while (lights_iter != NULL)
	{
		cur_light = ((t_light *)lights_iter->content);
		light_dir = sub(cur_light->position, cur_pos);
		n_dot_l = dot(normal, light_dir);
		if (n_dot_l > 0)
		{
			if (shadows(cur_pos, light_dir, data->objects) == FALSE)
			{
				n_dot_l /= length(normal) * length(light_dir);
				intensity += cur_light->intensity * n_dot_l;// div by zero
			}
		}
		lights_iter = lights_iter->next;
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
	//printf("t = %f\n", intxn.t);
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

void	fill_image(t_global *data, t_image *cur_image, t_camera *cur_camera)
{
	size_t	x;
	size_t	y;
	size_t	view_width;
	size_t	view_height;
	double	half_width;
	double	half_height;
	double	pixel_size;
	int		color;
	unsigned int	converted_color;
	t_ray	ray;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	double		right_factor;
	double		up_factor;

	ray.origin = cur_camera->origin;
	forward = unit(sub(cur_camera->direction, ray.origin));
	printf("forward = ");
	print_vec(forward);
	right = unit(cross(forward, (t_vector){0.0, 1.0, 0.0}));
	up = cross(right, forward);
	printf("right = ");
	print_vec(right);
	printf("up = ");
	print_vec(up);

	view_width = data->res[0];
	view_height = data->res[1];

	half_width = tan((M_PI * cur_camera->fov / 180) / 2);
	half_height = half_width * ((double)view_height / (double)view_width); // div by zero
	pixel_size = half_width * 2 / (double)view_width;

//	ray.direction.x += -1 * half_width + pixel_size / 2;
//	ray.direction.y += 1 * half_height - pixel_size / 2;
	ray.direction = add(add(forward, mult(right, -1 * half_width)), mult(up, 1 * half_height));
	printf("dir.x = %f, dir.y = %f (x = 0, y = 0)\n", ray.direction.x, ray.direction.y);

	y = 0;
	while (y < view_height)
	{
		x = 0;
		while (x < view_width)
		{
			right_factor = (2 * (double)x) / (double)view_width - 1;
			up_factor = (-2 * (double)y) / (double)view_height + 1;
			ray.direction = add(add(forward, mult(right, right_factor * half_width)), mult(up, up_factor * half_height));
//			if (x == 0)
//			{
//				printf("ray.dir = ");
//				print_vec(ray.direction);
//			}
			color = process_pixel(ray, data);
			converted_color = (unsigned)mlx_get_color_value(data->mlx_ptr, color);
			image_pixel_put(cur_image, x, y, converted_color);
			x++;
		}
		y++;
	}
	printf("dir.x = %f, dir.y = %f (x = %zu, y = %zu)\n", ray.direction.x, ray.direction.y, x - 1, y - 1);
}

t_bool	draw_images(t_global *data)
{
	t_list	*cameras_iter;
	t_image	*cur_image;

	cameras_iter = data->cameras;
	while (cameras_iter != NULL)
	{
		cur_image = new_image(data);
		fill_image(data, cur_image, ((t_camera *)cameras_iter->content));
		cameras_iter = cameras_iter->next;
	}
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_global	*data;

	if (argc != 2) // to change for export bmp
		error(ARG_MISSING_ERROR);
	data = parse_rtfile(argv[1]);
	errno = 0;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		free_data(data);
		error(MLX_INIT_ERROR);
	}
	check_resolution(data);
	draw_images(data);
	errno = 0;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->res[0], data->res[1], "miniRT");
	if (data->win_ptr == NULL)
	{
		free_data(data);
		error(MLX_NEW_WINDOW_ERROR);// free mlx_init
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			((t_image *)data->images->content)->ptr, 0, 0);
	mlx_key_hook(data->win_ptr, &key_hooks, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
