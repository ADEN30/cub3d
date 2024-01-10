SRCS	= src/main.c \
		  src/error/print_error.c \
		  src/hook/move.c \
		  src/hook/move2.c \
		  src/map/create_tab.c \
		  src/map/init_graphic.c \
		  src/map/init_graphic2.c \
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

SRCSBONUS	= src/bonus/main_bonus.c \
			src/bonus/print_error_bonus.c \
			src/bonus/mouse_bonus.c \
			src/bonus/move_bonus.c \
			src/bonus/move2_bonus.c \
			src/bonus/create_tab_bonus.c \
			src/bonus/init_graphic_bonus.c \
		  	src/bonus/init_graphic2_bonus.c \
			src/bonus/parse_map_bonus.c \
		  	src/bonus/parse_map_check_bonus.c \
		  	src/bonus/parse_map_check2_bonus.c \
		  	src/bonus/parse_style_bonus.c \
		  	src/bonus/parse_style2_bonus.c \
		  	src/bonus/parse_style3_bonus.c \
		  	src/bonus/ray_bonus.c \
		  	src/bonus/ray_h_bonus.c \
		  	src/bonus/ray_v_bonus.c \
		  	src/bonus/ray_vh_bonus.c \
		  	src/bonus/ray_tools_bonus.c \
		  	src/bonus/minimap_rays_bonus.c \
		  	src/bonus/show_view_bonus.c \
		  	src/bonus/show_minimap_bonus.c \
		  	src/bonus/wall_pixel_bonus.c \
		  	src/bonus/color_bonus.c \
		  	src/bonus/free_all_bonus.c \
		  	src/bonus/init_struct_bonus.c \
		  	src/bonus/tools_bonus.c \

OBJS		= $(SRCS:.c=.o)

OBJSBONUS	= $(SRCSBONUS:.c=.o)

HEAD		= -I include -I MLX42/include/MLX42 -I libft/include

HEADBONUS	= -I src/bonus/ -I MLX42/include/MLX42 -I libft/include

NAME		= cub3d

NAMEBONUS	= cub3d_bonus

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

bonus: $(OBJSBONUS)
	@if [ ! -f "./libft/libft.a" ]; then \
		$(MAKE) -C libft; \
	fi
	@$(CC) $(CFLAGS) $(HEADBONUS) $(OBJSBONUS) $(LIBS) -o $(NAMEBONUS)

clean:
	@if [ -f "./libft/src/ft_atoi.o" ]; then \
		make clean -C libft; \
	fi
	@if [ -f "./src/main.o" ]; then \
		$(RM) $(OBJS); \
	fi
	@if [ -f "./src/bonus/main_bonus.o" ]; then \
		$(RM) $(OBJSBONUS); \
	fi

fclean:
	@if [ -f "./libft/libft.a" ]; then \
		make fclean -C libft; \
	fi
	@if [ -f "./cub3d" ]; then \
		$(RM) $(OBJS); \
		$(RM) $(NAME); \
	fi
	@if [ -f "./cub3d_bonus" ]; then \
		$(RM) $(OBJSBONUS); \
		$(RM) $(NAMEBONUS); \
	fi

re:	fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re mlx42 bonus rebonus
