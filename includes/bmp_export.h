/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_export.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:47:21 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/07/20 19:57:45 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_EXPORT_H
# define BMP_EXPORT_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# include "ray_tracing.h"
# include "data_management.h"
# include "errors.h"
# include "minirt.h"

# define NB_PIXELS_MAX			132710400

# define BMP_METADATA_SIZE		54
# define BMP_INFOHEADER_SIZE	40
# define BMP_NB_COLOR_PLANES	1
# define BMP_BITS_PER_PIXEL		24

void	export_in_bmp(t_global *data, char *rtfile_name);

#endif
