/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:01:06 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/17 16:26:21 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef	enum	e_error_code
{
	ARGC_ERROR, //0
	RTFILE_NAME_ERROR, //1
	SAVE_OPTION_ERROR, //2
	NO_CAMERA_ERROR, //3
	RESOLUTION_MISSING_ERROR, //4
	OPEN_ERROR, //5
	CLOSE_ERROR, //6
	MALLOC_ERROR, //7
	GNL_ERROR, //8
	MLX_INIT_ERROR, //9
	MLX_SCREEN_SIZE_ERROR, //10
	MLX_NEW_WINDOW_ERROR, //11
	MLX_NEW_IMAGE_ERROR, //12
	NB_ERRORS
}				t_error_code;

# define E0 "A scene description file with the .rt extension must be given \n"\
	"as argument, with an optional --save option to save the rendered \n"\
	"image in bmp format.\n"
# define E1 "The name of the file given as argument must end with '.rt'.\n"
# define E2 "Only a --save option is allowed as second argument.\n"
# define E3 "There must be at least one camera in the scene.\n"
# define E4 "Image resolution must be defined to export a bmp file.\n"
# define E5 "Cannot open file"
# define E6 "Cannot close file descriptor previously opened for .rt file"
# define E7 "Cannot allocate required memory"
# define E8 "Cannot read file or allocate memory"
# define E9 "The MinilibX initialization failed"
# define E10 "MinilibX problem retrieving the actual display size"
# define E11 "MinilibX problem creating a new window"
# define E12 "MinilibX problem creating a new image"

# define E_RES "Resolution parameters not valid, "\
	"or declared twice in the file.\n"\
	"The following must be specified in order:\n"\
	"· x render size\n"\
	"· y render size\n"\
	"e.g. R 1920 1080\n"
# define E_AMB "Ambient lightning parameters not valid, "\
	"or declared twice in the file.\n"\
	"The following must be specified in order:\n"\
	"· ambient lighting ratio in range [0.0,1.0]: 0.2\n"\
	"· R,G,B colors in range [0-255]: 255, 255, 255\n"\
	"e.g. A 0.2 255,255,255\n"
# define E_CAM "Camera parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates of the view point: 0.0,0.0,20.6\n"\
	"· 3d normalized orientation vector.\n"\
	"\tIn range [-1,1] for each x,y,z axis: 0.0,0.0,1.0\n"\
	"· FOV : Horizontal field of view in degrees in range [0,180]\n"\
	"e.g. c -50.0,0,20 0,0,1 70\n"
# define E_LIG  "Light parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates of the light point: 0.0,0.0,20.6\n"\
	"· the light brightness ratio in range [0.0,1.0]: 0.6\n"\
	"· R,G,B colors in range [0-255]: 10, 0, 255\n"\
	"e.g. l -40.0,50.0,0.0 0.6 10,0,255\n"
# define E_SPH "Sphere parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates of the sphere center: 0.0,0.0,20.6\n"\
	"· the sphere diameter: 12.6\n"\
	"· R,G,B colors in range [0-255]: 10, 0, 255\n"\
	"e.g. sp 0.0,0.0,20.6 12.6 10,0,255\n"
# define E_PLA "Plane parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates: 0.0,0.0,-10.0\n"\
	"· 3d normalized orientation vector.\n"\
	"\tIn range [-1,1] for each x,y,z axis: 0.0,0.0,1.0\n"\
	"· R,G,B colors in range [0-255]: 0, 0, 255\n"\
	"e.g. pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225\n"
# define E_SQU "Square parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates of the square center: 0.0,0.0,20.6\n"\
	"· 3d normalized orientation vector.\n"\
	"\tIn range [-1,1] for each x,y,z axis: 1.0,0.0,0.0\n"\
	"· side size: 12.6\n"\
	"· R,G,B colors in range [0-255]: 255, 0, 255\n"\
	"e.g. sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255\n"
# define E_CYL "Cylinder parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates: 50.0,0.0,20.6\n"\
	"· 3d normalized orientation vector.\n"\
	"\tIn range [-1,1] for each x,y,z axis: 0.0,0.0,1.0\n"\
	"· the cylinder diameter: 14.2\n"\
	"· the cylinder height: 21.42\n"\
	"· R,G,B colors in range [0,255]: 10, 0, 255\n"\
	"e.g. cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255\n"
# define E_TRI "Triangle parameters not valid.\n"\
	"The following must be specified in order:\n"\
	"· x,y,z coordinates of the first point: 10.0,20.0,10.0\n"\
	"· x,y,z coordinates of the second point: 10.0,10.0,20.0\n"\
	"· x,y,z coordinates of the third point: 20.0,10.0,10.0\n"\
	"· R,G,B colors in range [0,255]: 0, 255, 255\n"\
	"e.g. tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255\n"
# define E_ID "Line does not begin with a proper element type identifier.\n"\
	"Possible identifiers: R A c l sp pl sq cy tr\n"

void	parsing_error_exit(size_t line_nb, uint8_t type_index, t_global *data);
void	error_and_exit(t_error_code err_code);

#endif
