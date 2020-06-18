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

SRCS		+= main.c
SRCS		+= vectors.c
SRCS		+= ray_tracing.c
SRCS		+= object_equations.c
SRCS		+= mlx_handling.c
SRCS		+= bmp_export.c
SRCS		+= errors.c
SRCS		+= list_utils.c
SRCS		+= free_utils.c

SRCS		+= parsing.c
SRCS		+= parse_res_cameras_lights.c
SRCS		+= parse_objects.c
SRCS		+= atoi_derivates.c
SRCS		+= parse_utils.c
SRCS		+= skip_wrap_utils.c

HDRS		+= minirt.h
HDRS		+= vectors.h
HDRS		+= parsing.h
HDRS		+= ray_tracing.h
HDRS		+= mlx_handling.h
HDRS		+= bmp_export.h
HDRS		+= errors.h

INCDIR		= includes/
SRCDIR		= sources/
SRCDIR		+= sources/parsing/
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
#remove this flag
LDFLAGS		+= -fsanitize=address,undefined

LDLIBS		+= -lft
LDLIBS		+= -lmlx
LDLIBS		+= -lm

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SRCS	+= mac_specific.c
	MLXDIR	= minilibx_mms_20200219/
else
	SRCS	+= linux_specific.c
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

# FORCE in dependency of the two libs to always run
$(LIBFTDIR)libft.a:
					$(MAKE) -C $(LIBFTDIR) bonus custom

$(MLXDIR)libmlx.a:
					$(MAKE) -C $(MLXDIR)

clean:
					$(RM) -r $(OBJDIR)

fclean:				clean
					$(RM) $(NAME)


re:					fclean all

# FORCE: (nothing in the rule; add to .PHONY too)

.PHONY:				all clean fclean re
