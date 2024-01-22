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
		  src/map/parse_style3.c \
		  src/raycasting/ray.c \
		  src/raycasting/ray_h.c \
		  src/raycasting/ray_v.c \
		  src/raycasting/ray_vh.c \
		  src/raycasting/ray_tools.c \
		  src/show3d/show_view.c \
		  src/show3d/wall_pixel.c \
		  src/style/color.c \
		  src/utils/free_all.c \
		  src/utils/init_struct.c \
		  src/utils/tools.c 

OBJS		= $(SRCS:.c=.o)

HEAD		= -I include -I MLX42/include/MLX42 -I libft/include

NAME		= cub3D

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -Ofast

LIBS		= libft/libft.a MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

all		:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $(<:.c=.o)

mlx42 :
	@if [ ! -d "./MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@if [ ! -f "MLX42/build/libmlx42.a" ]; then \
		cmake -S ./MLX42 -B ./MLX42/build; \
		make -C ./MLX42/build -j4; \
	fi

$(NAME)	: $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(HEAD) $(OBJS) $(LIBS) -o $(NAME)

debug:
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -fsanitize=address $(HEAD) $(SRCS) $(LIBS) -o $(NAME)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS)

fclean:
	$(MAKE) fclean -C libft
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:	fclean all

debugbonus:
	$(MAKE) debug -C src/bonus

bonus:
	$(MAKE) -C src/bonus

cleanbonus:
	$(MAKE) clean -C src/bonus

fcleanbonus:
	$(MAKE) fclean -C src/bonus

rebonus: fcleanbonus bonus

.PHONY: all mlx42 debug clean fclean re bonus bonusdebug cleanbonus fcleanbonus rebonus
