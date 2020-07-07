# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/23 13:17:34 by mvidal-a          #+#    #+#              #
#    Updated: 2020/07/08 00:18:25 by mvidal-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		+= main.c
#SRCS		+= obj_extract_triangles.c
#SRCS		+= obj_extract_triangles_parsing.c

SRCS		+= ray_tracing.c
SRCS		+= ray_tracing_utils.c
SRCS		+= shading.c
SRCS		+= scene_properties.c
SRCS		+= view_properties.c
SRCS		+= object_view_properties.c
SRCS		+= object_equations.c
SRCS		+= object_equations_lightray.c
SRCS		+= object_equations_utils.c
SRCS		+= object_normals.c

SRCS		+= mlx_display.c
SRCS		+= key_mouse_hooks.c
SRCS		+= hook_functions.c

SRCS		+= bmp_export.c

SRCS		+= parsing.c
SRCS		+= parse_res_cameras_lights.c
SRCS		+= parse_objects.c
SRCS		+= atoi_derivates.c
SRCS		+= parse_utils.c
SRCS		+= skip_wrap_utils.c

SRCS		+= pixel_put_to_str.c
SRCS		+= rgb_utils.c
SRCS		+= list_utils.c
SRCS		+= free_utils.c

SRCS		+= vectors.c
SRCS		+= vectors2.c
SRCS		+= vectors3.c

SRCS		+= errors.c
SRCS		+= parsing_error_msg.c

SRCDIR		+= sources/
SRCDIR		+= sources/ray_tracing/
SRCDIR		+= sources/mlx_display/
SRCDIR		+= sources/bmp_export/
SRCDIR		+= sources/parsing/
SRCDIR		+= sources/data_management/
SRCDIR		+= sources/vectors/
SRCDIR		+= sources/errors/

HDRS		+= minirt.h
HDRS		+= ray_tracing.h
HDRS		+= mlx_display.h
HDRS		+= bmp_export.h
HDRS		+= parsing.h
HDRS		+= data_management.h
HDRS		+= vectors.h
HDRS		+= errors.h

INCDIR		= includes/

LIBFTDIR	= libft/

OBJDIR		= objects/

OBJS		= $(addprefix $(OBJDIR), $(SRCS:.c=.o))

vpath %.c $(SRCDIR)
vpath %.h $(INCDIR)

CC			= clang

CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Werror
CFLAGS		+= -fsanitize=address,undefined
CFLAGS		+= -Wpadded
#CFLAGS		+= -g3

CPPFLAGS	+= -I $(INCDIR)
CPPFLAGS	+= -I $(LIBFTDIR)
CPPFLAGS	+= -I $(MLXDIR)

LDFLAGS		+= -L $(LIBFTDIR)
LDFLAGS		+= -L $(MLXDIR)
LDFLAGS	+= -fsanitize=address,undefined

LDLIBS		+= -lft
LDLIBS		+= -lmlx
LDLIBS		+= -lm

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	MLXDIR		= minilibx_mms_20200219/
	MLXLIB		= libmlx.dylib
	CPPFLAGS 	+= -D PLATFORM_MACOS
	LDFLAGS		+= -Xlinker -dylib_file -Xlinker libmlx.dylib:minilibx_mms_20200219/libmlx.dylib
else
	MLXDIR		= minilibx-linux/
	MLXLIB		= libmlx.a
	LDLIBS		+= -lXext
	LDLIBS		+= -lX11
	CPPFLAGS 	+= -D PLATFORM_LINUX
endif

all:				$(NAME)

$(NAME):			$(LIBFTDIR)libft.a $(MLXDIR)$(MLXLIB) $(OBJS)
					$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
ifeq ($(UNAME_S),Darwin)
					install_name_tool -change libmlx.dylib minilibx_mms_20200219/libmlx.dylib miniRT
endif

$(OBJDIR)%.o:		%.c
					$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS):			$(HDRS) | $(OBJDIR)

$(OBJDIR):
					mkdir $@

# FORCE in dependency of the two libs to always run
$(LIBFTDIR)libft.a:
					$(MAKE) -C $(LIBFTDIR) bonus custom

$(MLXDIR)$(MLXLIB):
					$(MAKE) -C $(MLXDIR)

#add clean for mlx and libft?
clean:
					$(RM) -r $(OBJDIR)

fclean:				clean
					$(RM) $(NAME)


re:					fclean all

# FORCE: (nothing in the rule; add to .PHONY too)

.PHONY:				all clean fclean re
