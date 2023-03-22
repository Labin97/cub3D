NAME 		= cub3D
# CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= includes
mlx_LIB 	= -lmlx -framework OpenGL -framework AppKit
SOURCES 	= srcs/main.c\
			srcs/init_color_texture.c\
			srcs/error.c\
			srcs/map_parsing.c\
			srcs/init_map.c

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C libft
	cc $^ -Llibft -lft -o $@

%.o : %.c
	cc $(CFLAGS) -Ilibft/includes -I$(INCLUDES) -c $^ -o $@

clean :
	make clean -C libft
	rm -f $(OBJECTS)

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
