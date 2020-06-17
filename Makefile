# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/23 13:17:34 by mvidal-a          #+#    #+#              #
#    Updated: 2020/06/17 16:27:14 by mvidal-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		+= minirt.c
SRCS		+= parsing.c
SRCS		+= parse_types.c
SRCS		+= parse_utils.c
SRCS		+= vectors.c
SRCS		+= mlx_handling.c
SRCS		+= bmp_export.c
SRCS		+= errors.c

HDRS		= minirt.h

INCDIR		= includes/
SRCDIR		= sources/
OBJDIR		= objects/
LIBFTDIR	= libft/

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
LDFLAGS		+= -fsanitize=address,undefined #remove it

LDLIBS		+= -lft
LDLIBS		+= -lmlx
LDLIBS		+= -lm

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SRCS	+= screen_res_mac.c
	MLXDIR	= minilibx_opengl_20191021/
	LDLIBS	+= -framework OpenGL
	LDLIBS	+= -framework AppKit
else
	SRCS	+= screen_res_linux.c
	MLXDIR	= minilibx-linux/
	LDLIBS	+= -lXext
	LDLIBS	+= -lX11
endif

all:				$(NAME)

$(NAME):			$(LIBFTDIR)libft.a $(MLXDIR)libmlx.a $(OBJS)
					$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJDIR)%.o:		%.c
					$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS):			$(HDRS) | $(OBJDIR)

$(OBJDIR):
					mkdir $@

$(LIBFTDIR)libft.a:	#FORCE
					$(MAKE) -C $(LIBFTDIR) bonus custom

$(MLXDIR)libmlx.a:	#FORCE
					$(MAKE) -C $(MLXDIR)

clean:
					$(RM) -r $(OBJDIR)

fclean:				clean
					$(RM) $(NAME)


re:					fclean all

#FORCE:

.PHONY:				all clean fclean re #FORCE
