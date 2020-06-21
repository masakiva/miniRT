/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:37:19 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/18 16:34:04 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>

# include "vectors.h"
# include "errors.h"
# include "minirt.h"

# define RES	"R"
# define AMB	"A"
# define CAM	"c"
# define LIG	"l"
# define SPH	"sp"
# define PLA	"pl"
# define SQU	"sq"
# define CYL	"cy"
# define TRI	"tr"
# define NB_ELEM	9

typedef const char	*(*t_parse)(const char *, t_global *);

t_global		*parse_rtfile(const char *rtfile);

const char		*p_resolution(const char *line, t_global *data);
const char		*p_ambient_lighting(const char *line, t_global *data);
const char		*p_camera(const char *line, t_global *data);
const char		*p_light(const char *line, t_global *data);

const char		*p_sphere(const char *line, t_global *data);
const char		*p_plane(const char *line, t_global *data);
const char		*p_square(const char *line, t_global *data);
const char		*p_cylinder(const char *line, t_global *data);
const char		*p_triangle(const char *line, t_global *data);

const char		*skip_spaces_tabs(const char *str);
const char		*skip_comma(const char *str);
const char		*skip_int(const char *str);
const char		*skip_float(const char *str);

int8_t			atoi_sign(const char *str, int *nb);
double			atof_decimal_part(const char *str);
int8_t			atof_double(const char *str, double *nb_f);
const char		*parse_int(const char *line, int *i);
const char		*parse_float(const char *line, double *f);
const char		*parse_coord(const char *line, t_point *v);
const char		*parse_unit_vector(const char *line, t_vector *v);
const char		*parse_color(const char *line, t_rgb *color);
t_rgb			*wrap_object(void *cur_obj, t_list **lst, uint8_t type);

#endif
