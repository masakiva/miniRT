#include "minirt.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	OC = sub(ray->origin, sp->centre);// a mettre en cache? ->liste chainee dans sp
	//ray.direction = sub(ray.direction, ray.origin);
	a = length_sq(ray->direction);
	b = 2 * dot(ray->direction, OC);
	c = length_sq(OC) - sq(sp->radius);
	discriminant = sq(b) - 4 * a * c; // 4c a mettre en cache?
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
	t = 2147483647;
	if (d_dot_n != 0)
	{
		t = dot(pl->normal, sub(pl->position, ray->origin)) / d_dot_n;
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
		i_square, i_cylinder, i_triangle*/}; //i_ -> intersect_
	double			cur_t;
	t_list			*closest_elem;
	double			closest_t;

	closest_t = t_max;
	closest_elem = NULL;
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
		n_square, n_cylinder, n_triangle*/}; //n_ -> normal_
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
	intxn = closest_intersection(ray, data->objects, 1, 2147483647); // 1 pose pb pour le plan ; define ces constantes
	//printf("t = %f\n", intxn.t);
	if (intxn.t == 2147483647)
		color = (t_rgb){0.0, 0.0, 0.0}; // ou blanc?
	else
	{
		color = ((t_obj *)intxn.obj->content)->color;
		position = add(ray.origin, mult(ray.direction, intxn.t));
		light = lighting(position, intxn.obj, data);
		color = mult(color, light + data->amb_light);
	}
	return (rgb_to_int(color));
}

void	get_view_properties(t_global *data, t_view_properties *props, t_camera *cur_camera)
{
	props->half_height = cur_camera->half_width *
		((double)data->res[1] / (double)data->res[0]);
	props->half_pixel_width = cur_camera->half_width / (double)data->res[0];
	props->x_factor = -1;
	props->x_factor_i = 2 / (double)data->res[0];
	props->x_factor_vec = mult(cur_camera->right_vec,
			props->x_factor * cur_camera->half_width + props->half_pixel_width);
	props->y_factor = 1;
	props->y_factor_i = 2 / (double)data->res[1];
	props->y_factor_vec = mult(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
}

void	next_pixel_x(t_camera *cur_camera, t_view_properties *props)
{
	props->x_factor += props->x_factor_i;
	props->x_factor_vec = mult(cur_camera->right_vec,
		props->x_factor * cur_camera->half_width + props->half_pixel_width);
}

void	next_row_y(t_camera *cur_camera, t_view_properties *props)
{
	props->y_factor -= props->y_factor_i;
	props->y_factor_vec = mult(cur_camera->up_vec,
			props->y_factor * props->half_height - props->half_pixel_width);
	props->x_factor = -1;
}

void	fill_image(t_global *data, t_image *cur_image, t_camera *cur_camera)
{
	size_t				x;
	size_t				y;
	int					color;
	t_ray				ray;
	t_view_properties	props;

	get_view_properties(data, &props, cur_camera);
	ray.origin = cur_camera->origin;
	y = 0;
	while (y < data->res[1])
	{
		x = 0;
		while (x < data->res[0])
		{
			ray.direction = add(cur_camera->forward_vec,
						add(props.x_factor_vec, props.y_factor_vec));
			if (x == 0 && y == 0)
			{
				printf("ray.dir (x = %4zu, y = %4zu) = ", x, y);
				print_vec(ray.direction);
			}
			color = process_pixel(ray, data);
			pixel_put_converted_color(data, cur_image, (size_t[2]){x, y}, color);
			next_pixel_x(cur_camera, &props);
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
	printf("ray.dir (x = %4zu, y = %4zu) = ", x - 1, y - 1);
	print_vec(ray.direction);
	printf("\n");
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

void	render_with_mlx(t_global *data)
{
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
		error(MLX_NEW_WINDOW_ERROR);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			((t_image *)data->images->content)->ptr, 0, 0);
	mlx_key_hook(data->win_ptr, &key_hooks, data);
	mlx_loop(data->mlx_ptr);
}

void	uint_to_str_little_endian(unsigned nb, char *str)
{
	str[0] = (char)nb;
	str[1] = (char)(nb >> 8);
	str[2] = (char)(nb >> 16);
	str[3] = (char)(nb >> 24);
}

char	*get_bmpfile_name(char *basename, int index)
{
	char	*index_str;
	char	*suffix;
	char	*bmpfile_name;

	errno = 0;
	if (index == 0)
		suffix = ft_strdup(".bmp");
	else
	{
		index_str = ft_itoa(index);
		if (index_str == NULL)
			error(MALLOC_ERROR); // new code
		errno = 0;
		suffix = ft_strjoin(index_str, ".bmp");
		free(index_str);
	}
	if (suffix == NULL)
		error(MALLOC_ERROR); // new code
	errno = 0;
	bmpfile_name = ft_strjoin(basename, suffix);
	free(suffix);
	if (bmpfile_name == NULL)
		error(MALLOC_ERROR); // new code
	return (bmpfile_name);
}

int		create_bmpfile(const char *rtfile_name, t_global *data)
{
	int		fd;
	char	*basename;
	char	*bmpfile_name;
	int		i;

	basename = ft_strrchr(rtfile_name, '/') + 1;
	basename[ft_strlen(basename) - 3] = '\0';
	fd = ERROR;
	i = 0;
	while (fd == ERROR)
	{
		bmpfile_name = get_bmpfile_name(basename, i);
		fd = open(bmpfile_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
		free(bmpfile_name);
		if (fd == ERROR && errno != EEXIST)
		{
			free_data(data);
			error(OPEN_ERROR); // another code
		}
		i++;
	}
	return (fd);
}

void	export_in_bmp(t_global *data, const char *rtfile_name)
{
	size_t	line_padding;
	size_t	file_size;
	char	*file_data;
	int		fd;

	fd = create_bmpfile(rtfile_name, data);
	return ;
	line_padding = 0;
	if ((data->res[0] * 3) % 4 != 0)
		line_padding = 4 - (data->res[0] * 3) % 4;
	printf("line_padding = %zu\n", line_padding);
	file_size = BMP_METADATA_SIZE + (data->res[0] * 3 + line_padding) * data->res[1];
	errno = 0;
	file_data = (char *)malloc(file_size * sizeof(char));
	if (file_data == NULL)
	{
		free_data(data);
		close(fd);
		error(MALLOC_ERROR); // another code?
	}
	ft_bzero(file_data, file_size);
	file_data[0x0] = 'B';
	file_data[0x1] = 'M';
	uint_to_str_little_endian((unsigned)file_size, file_data + 0x2);
	file_data[0xA] = BMP_METADATA_SIZE;
	uint_to_str_little_endian((unsigned)data->res[0], file_data + 0x12);
	uint_to_str_little_endian((unsigned)data->res[1], file_data + 0x16);
	file_data[0xE] = BMP_INFOHEADER_SIZE;
	file_data[0x1A] = BMP_NB_COLOR_PLANES;
	file_data[0x1C] = BMP_BITS_PER_PIXEL;

	size_t				x;
	size_t				y;
	int					color;
	t_ray				ray;
	t_view_properties	props;
	t_camera			*cur_camera;
	size_t				i;
	char				*data_addr;

	cur_camera = (t_camera *)data->cameras->content;
	get_view_properties(data, &props, cur_camera);
	ray.origin = cur_camera->origin;
	i = BMP_METADATA_SIZE;
	data_addr = file_data + i;
	y = 0;
	while (y < data->res[1])
	{
		i = (data->res[1] - y - 1) * (data->res[0] * 3 + line_padding);
		x = 0;
		while (x < data->res[0])
		{
			ray.direction = add(cur_camera->forward_vec,
						add(props.x_factor_vec, props.y_factor_vec));
			color = process_pixel(ray, data);
			data_addr[i] = color;
			data_addr[i + 1] = color >> 8;
			data_addr[i + 2] = color >> 16;
			next_pixel_x(cur_camera, &props);
			i += 3;
			x++;
		}
		next_row_y(cur_camera, &props);
		y++;
	}
	printf("file_size = %zu\n", file_size);
	write(fd, file_data, file_size);
	close(fd);
	free(file_data);
}

void	check_rtfile_name(const char *file_name)
{
	if (ft_memcmp(file_name + ft_strlen(file_name) - 3, ".rt", 4) != 0)
		error(RTFILE_NAME_ERROR);
}

void	check_save_option(const char *option)
{
	if (ft_memcmp(option, "--save", 7) != 0)
		error(SAVE_OPTION_ERROR);
}

int		main(int argc, char **argv)
{
	t_global	*data;

	data = NULL;
	if (argc < 2 || argc > 3)
		error(ARGC_ERROR);
	else if (argc == 2)
	{
		check_rtfile_name(argv[1]);
		data = parse_rtfile(argv[1]);
		render_with_mlx(data);
	}
	else if (argc == 3)
	{
		check_rtfile_name(argv[1]);
		check_save_option(argv[2]);
		data = parse_rtfile(argv[1]);
		export_in_bmp(data, argv[1]);
		free_data(data);
	}
//	t_list			*images_iter;
//
//	images_iter = data->images;
//	while (images_iter != NULL)
//	{
//		mlx_destroy_image(data->mlx_ptr, ((t_image *)images_iter->content)->ptr);// err?
//		images_iter = images_iter->next;
//	}
//	free_data(data);
	return (EXIT_SUCCESS);
}
