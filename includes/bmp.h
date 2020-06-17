/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:47:21 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:58:15 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# define BMP_METADATA_SIZE 54
# define BMP_INFOHEADER_SIZE 40
# define BMP_NB_COLOR_PLANES 1
# define BMP_BITS_PER_PIXEL 24

void			export_in_bmp(t_global *data, const char *rtfile_name);

#endif
