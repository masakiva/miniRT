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
SRCS		+= errors.c

HEADERS		= minirt.h

OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

OBJDIR		= objects

CC			= clang

CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Werror
#CFLAGS		+= -fsanitize=address
CFLAGS		+= -Wpadded
#CFLAGS		+= -g3

CPPFLAGS	+= -I ./
CPPFLAGS	+= -I ../libft/
CPPFLAGS	+= -I ../minilibx-linux/

LDFLAGS		+= -L ./
LDFLAGS		+= -L ../libft/
LDFLAGS		+= -L ../minilibx-linux/
#LDFLAGS		+= -fsanitize=address

LDLIBS		+= -lft
LDLIBS		+= -lmlx
LDLIBS		+= -lXext
LDLIBS		+= -lX11
LDLIBS		+= -lm

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o:	%.c
				$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS):		$(HEADERS) | $(OBJDIR)

$(OBJDIR):
				mkdir $@

clean:
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)


re:				fclean all

.PHONY:			all clean fclean re
