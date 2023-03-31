NAME 		= cub3D
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= includes
mlx_LIB 	= -lmlx -framework OpenGL -framework AppKit
SOURCES 	= srcs/init_color.c\
			srcs/init_texture.c\
			srcs/error.c\
			srcs/map_parsing.c\
			srcs/init_map.c\
			srcs/run.c\
			srcs/mlx_init.c\
			srcs/projection.c\
			srcs/projection2.c\
			srcs/mlx_color.c\
			srcs/texture_set.c\
			srcs/render_frame.c\
			srcs/hook.c
B_SOURCES	= b_srcs/init_color_bonus.c\
			b_srcs/init_texture_bonus.c\
			b_srcs/error_bonus.c\
			b_srcs/map_parsing_bonus.c\
			b_srcs/init_map_bonus.c\
			b_srcs/run_bonus.c\
			b_srcs/mlx_init_bonus.c\
			b_srcs/projection_bonus.c\
			b_srcs/projection2_bonus.c\
			b_srcs/mlx_color_bonus.c\
			b_srcs/texture_set_bonus.c\
			b_srcs/render_frame_bonus.c\
			b_srcs/hook_bonus.c

OBJS = $(SOURCES:.c=.o)
B_OBJS = $(B_SOURCES:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(B_OBJS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C libft
	cc $^ -Llibft -lft $(mlx_LIB) -o $@

bonus :
	@ make WITH_BONUS=1 all

%.o : %.c
	cc $(CFLAGS) -Ilibft/includes -I$(INCLUDES) -c $^ -o $@

clean :
	make clean -C libft
	rm -f $(OBJS) $(B_OBJS)

fclean : 
	make clean
	make fclean -C libft
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all bonus clean fclean re
