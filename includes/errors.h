/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:01:06 by mvidal-a          #+#    #+#             */
/*   Updated: 2020/06/25 14:13:59 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>
# include <errno.h>

# include "minirt.h"

typedef	enum	e_error_code
{
	ARGC_ERROR, //0
	RTFILE_NAME_ERROR, //1
	SAVE_OPTION_ERROR, //2
	NO_CAMERA_ERROR, //3
	RESOLUTION_MISSING_ERROR, //4
	OPEN_RTFILE_ERROR, //5
	CLOSE_RTFILE_ERROR, //6
	MALLOC_ERROR, //7
	GNL_ERROR, //8
	OPEN_BMPFILE_ERROR, //9
	WRITE_BMPFILE_ERROR, //10
	CLOSE_BMPFILE_ERROR, //11
	MLX_INIT_ERROR, //12
	MLX_SCREEN_SIZE_ERROR, //13
	MLX_NEW_WINDOW_ERROR, //14
	MLX_NEW_IMAGE_ERROR, //15
	NB_ERRORS
}				t_error_code;

# define E0_1 "A scene description file with the .rt extension must be \n"
# define E0_2 "given as argument, with an optional --save option to save \n"
# define E0_3 "the rendered image in bmp format.\n"
# define E1 "The name of the file given as argument must end with '.rt'.\n"
# define E2 "Only a --save option is allowed as second argument.\n"
# define E3 "There must be at least one camera in the scene.\n"
# define E4 "Image resolution must be defined to export a bmp file.\n"
# define E5 "Cannot open .rt file specified in argument"
# define E6 "Cannot close file descriptor previously opened for .rt file"
# define E7 "Cannot allocate required memory"
# define E8 "Cannot read .rt file or allocate memory (get_next_line error)"
# define E9 "Cannot open (create) .bmp file"
# define E10 "Cannot write data in the .bmp file previously created"
# define E11 "Could not close file descriptor previously opened for .bmp file"
# define E12 "The MinilibX initialization failed"
# define E13 "MinilibX problem retrieving the actual display size"
# define E14 "MinilibX problem creating a new window"
# define E15 "MinilibX problem creating a new image"

# define E_RES1 "Resolution parameters not valid, "
# define E_RES2 "or declared twice in the file.\n"
# define E_RES3 "The following must be specified in order:\n"
# define E_RES4 "· x render size\n"
# define E_RES5 "· y render size\n"
# define E_RES6 "e.g. R 1920 1080\n"
# define E_AMB1 "Ambient lighting parameters not valid, "
# define E_AMB2 "or declared twice in the file.\n"
# define E_AMB3 "The following must be specified in order:\n"
# define E_AMB4 "· ambient lighting ratio in range [0.0,1.0]: 0.2\n"
# define E_AMB5 "· R,G,B colors in range [0-255]: 255, 255, 255\n"
# define E_AMB6 "e.g. A 0.2 255,255,255\n"
# define E_SPH1 "Sphere parameters not valid.\n"
# define E_SPH2 "The following must be specified in order:\n"
# define E_SPH3 "· x,y,z coordinates of the sphere center: 0.0,0.0,20.6\n"
# define E_SPH4 "· the sphere diameter: 12.6\n"
# define E_SPH5 "· R,G,B colors in range [0-255]: 10, 0, 255\n"
# define E_SPH6 "e.g. sp 0.0,0.0,20.6 12.6 10,0,255\n"
# define E_PLA1 "Plane parameters not valid.\n"
# define E_PLA2 "The following must be specified in order:\n"
# define E_PLA3 "· x,y,z coordinates: 0.0,0.0,-10.0\n"
# define E_PLA4 "· 3d normalized orientation vector.\n"
# define E_PLA5 "\tIn range [-1,1] for each x,y,z axis: 0.0,0.0,1.0\n"
# define E_PLA6 "\tCannot be null (0.0,0.0,0.0)\n"
# define E_PLA7 "· R,G,B colors in range [0-255]: 0, 0, 255\n"
# define E_PLA8 "e.g. pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225\n"
# define E_TRI1 "Triangle parameters not valid.\n"
# define E_TRI2 "The following must be specified in order:\n"
# define E_TRI3 "· x,y,z coordinates of the first point: 10.0,20.0,10.0\n"
# define E_TRI4 "· x,y,z coordinates of the second point: 10.0,10.0,20.0\n"
# define E_TRI5 "· x,y,z coordinates of the third point: 20.0,10.0,10.0\n"
# define E_TRI6 "· R,G,B colors in range [0,255]: 0, 255, 255\n"
# define E_TRI7 "e.g. tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255\n"
# define E_SQU1 "Square parameters not valid.\n"
# define E_SQU2 "The following must be specified in order:\n"
# define E_SQU3 "· x,y,z coordinates of the square center: 0.0,0.0,20.6\n"
# define E_SQU4 "· 3d normalized orientation vector.\n"
# define E_SQU5 "\tIn range [-1,1] for each x,y,z axis: 1.0,0.0,0.0\n"
# define E_SQU6 "\tCannot be null (0.0, 0.0, 0.0) nor vertical (0.0, ?.?, 0.0)\n"
# define E_SQU7 "· side size: 12.6\n"
# define E_SQU8 "· R,G,B colors in range [0-255]: 255, 0, 255\n"
# define E_SQU9 "e.g. sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255\n"
# define E_CYL1 "Cylinder parameters not valid.\n"
# define E_CYL2 "The following must be specified in order:\n"
# define E_CYL3 "· x,y,z coordinates: 50.0,0.0,20.6\n"
# define E_CYL4 "· 3d normalized orientation vector.\n"
# define E_CYL5 "\tIn range [-1,1] for each x,y,z axis: 0.0,0.0,1.0\n"
# define E_CYL6 "\tCannot be null (0.0,0.0,0.0)\n"
# define E_CYL7 "· the cylinder diameter: 14.2\n"
# define E_CYL8 "· the cylinder height: 21.42\n"
# define E_CYL9 "· R,G,B colors in range [0,255]: 10, 0, 255\n"
# define E_CYL10 "e.g. cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255\n"
// lookat option for camera
# define E_CAM1 "Camera parameters not valid.\n"
# define E_CAM2 "The following must be specified in order:\n"
# define E_CAM3 "· x,y,z coordinates of the view point: 0.0,0.0,20.6\n"
# define E_CAM4 "· 3d normalized orientation vector.\n"
# define E_CAM5 "\tIn range [-1,1] for each x,y,z axis: 0.0,0.0,1.0\n"
# define E_CAM6 "\tCannot be null (0.0, 0.0, 0.0) nor vertical (0.0, ?.?, 0.0)\n"
# define E_CAM7 "· FOV : Horizontal field of view in degrees in range [0,180]\n"
# define E_CAM8 "e.g. c -50.0,0,20 0,0,1 70\n"
# define E_LIG1  "Light parameters not valid.\n"
# define E_LIG2 "The following must be specified in order:\n"
# define E_LIG3 "· x,y,z coordinates of the light point: 0.0,0.0,20.6\n"
# define E_LIG4 "· the light brightness ratio in range [0.0,1.0]: 0.6\n"
# define E_LIG5 "· R,G,B colors in range [0-255]: 10, 0, 255\n"
# define E_LIG6 "e.g. l -40.0,50.0,0.0 0.6 10,0,255\n"
# define E_ID1 "Line does not begin with a proper element type identifier.\n"
# define E_ID2 "Possible identifiers: R A c l sp pl sq cy tr\n"

void	putstr_stderr(const char *str);
void	print_elem_err_msg1(uint8_t type_index);
void	print_elem_err_msg2(uint8_t type_index);
void	print_elem_err_msg3(uint8_t type_index);
void	print_elem_err_msg4(uint8_t type_index);
void	print_elem_err_msg5(uint8_t type_index);
void	write_error(ssize_t bytes_written, size_t file_size);
void	parsing_error_exit(size_t line_nb, uint8_t type_index, t_global *data)
	__attribute__ ((noreturn));
void	error_and_exit(t_error_code err_code) __attribute__ ((noreturn));

#endif
