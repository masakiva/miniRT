# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/23 13:17:34 by mvidal-a          #+#    #+#              #
#    Updated: 2020/01/29 14:12:23 by mvidal-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		+= minirt.c
SRCS		+= parsing.c
SRCS		+= parse_types.c
SRCS		+= parse_utils.c
SRCS		+= vectors.c
SRCS		+= mlx_handling.c
SRCS		+= errors.c

HDRS		= minirt.h

INCDIR		= includes/
SRCDIR		= sources/
OBJDIR		= objects/
LIBFTDIR	= libft/
MLXDIR		= minilibx-linux/
#MLXDIR		= minilibx_opengl_20191021/

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
LDLIBS		+= -lXext
LDLIBS		+= -lX11
#LDLIBS		+= -framework OpenGL
#LDLIBS		+= -framework AppKit
LDLIBS		+= -lm

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
