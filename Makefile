SRCS	= src/main.c \
		  src/error/print_error.c \
		  src/hook/move.c \
		  src/hook/move2.c \
		  src/map/create_tab.c \
		  src/map/init_graphic.c \
		  src/map/parse_map.c \
		  src/map/parse_map_check.c \
		  src/map/parse_map_check2.c \
		  src/map/parse_style.c \
		  src/map/parse_style2.c \
		  src/raycasting/ray.c \
		  src/raycasting/ray_h.c \
		  src/raycasting/ray_v.c \
		  src/raycasting/ray_vh.c \
		  src/raycasting/ray_tools.c \
		  src/show3d/minimap_rays.c \
		  src/show3d/show_view.c \
		  src/show3d/show_minimap.c \
		  src/show3d/wall_pixel.c \
		  src/style/color.c \
		  src/utils/free_all.c \
		  src/utils/init_struct.c \
		  src/utils/tools.c \

OBJS		= $(SRCS:.c=.o)

HEAD		= -I include -I MLX42/include/MLX42 -I libft/include

NAME		= cub3d

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
#CFLAGS		= -Wall -Wextra -Werror 

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
