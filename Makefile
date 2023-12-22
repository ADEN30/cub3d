SRCS	= src/main.c \
		  src/test/print_error.c \
		  src/test/test.c \
		  src/utils/free_all.c \
		  src/utils/init_struct.c \
		  src/utils/tools.c \
		  src/map/create_map.c \
		  src/map/show_map.c \
		  src/style/color.c \
		  src/style/find_style.c \
		  src/hook/move.c \
		  src/raycasting/ray.c \
		  src/show3d/show.c \
		  src/show3d/init.c \

OBJS		= $(SRCS:.c=.o)

HEAD		= -I include -I MLX42/include/MLX42 -I libft/include

NAME		= cub3d

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -D MAP=1

LIBS		= libft/libft.a MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

all		:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $(<:.c=.o)

mlx42 :
	@if [ ! -d "./MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@if [ ! -e "MLX42/build/libmlx42.a" ]; then \
		cmake -S ./MLX42 -B ./MLX42/build; \
		make -C ./MLX42/build -j4; \
	fi

$(NAME)	: $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(HEAD) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@make clean -C libft
	$(RM) $(OBJS)

fclean:
	@make fclean -C libft
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re mlx42
