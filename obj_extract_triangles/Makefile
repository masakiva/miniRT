NAME		= extract_triangles

SRCS		+= obj_extract_triangles.c
SRCS		+= obj_parsing.c
SRCS		+= obj_parsing_utils.c

SRCDIR		= ./

HDRS		= obj_extract_triangles.h

INCDIR		= ./

LIBFTDIR	= libft/

OBJDIR		= objects/

OBJS		= $(addprefix $(OBJDIR), $(SRCS:.c=.o))

vpath %.c $(SRCDIR)
vpath %.h $(INCDIR)

CC			= clang

CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Werror
#CFLAGS		+= -fsanitize=address,undefined
#CFLAGS		+= -Wpadded
#CFLAGS		+= -g3

CPPFLAGS	+= -I $(INCDIR)
CPPFLAGS	+= -I $(LIBFTDIR)

LDFLAGS		+= -L $(LIBFTDIR)
#LDFLAGS	+= -fsanitize=address,undefined

LDLIBS		+= -lft

all:				$(NAME)

$(NAME):			$(LIBFTDIR)libft.a $(OBJS)
					$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJDIR)%.o:		%.c
					$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS):			$(HDRS) | $(OBJDIR)

$(OBJDIR):
					mkdir $@

$(LIBFTDIR)libft.a:
					$(MAKE) -C $(LIBFTDIR) bonus custom

clean:
					$(MAKE) -C $(LIBFTDIR) fclean
					$(RM) -r $(OBJDIR)

fclean:				clean
					$(RM) $(NAME)


re:					fclean all

.PHONY:				all clean fclean re
