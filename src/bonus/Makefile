SRCSBONUS	= main_bonus.c \
			print_error_bonus.c \
			move_bonus.c \
			move2_bonus.c \
			create_tab_bonus.c \
			init_graphic_bonus.c \
		  	init_graphic2_bonus.c \
			parse_map_bonus.c \
		  	parse_map_check_bonus.c \
		  	parse_map_check2_bonus.c \
		  	parse_style_bonus.c \
		  	parse_style2_bonus.c \
		  	parse_style3_bonus.c \
		  	ray_bonus.c \
		  	ray_h_bonus.c \
		  	ray_v_bonus.c \
		  	ray_vh_bonus.c \
		  	ray_tools_bonus.c \
		  	minimap_rays_bonus.c \
		  	show_view_bonus.c \
		  	show_minimap_bonus.c \
		  	wall_pixel_bonus.c \
		  	color_bonus.c \
		  	free_all_bonus.c \
		  	init_struct_bonus.c \
		  	tools_bonus.c \

OBJSBONUS	= $(SRCSBONUS:.c=.o)

HEAD		= -I ../../include -I ../../MLX42/include/MLX42 -I ../../libft/include

HEADBONUS	= -I ../../MLX42/include/MLX42 -I ../../libft/include

NAMEBONUS	= cub3d_bonus

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror
#CFLAGS		= -Wall -Wextra -Werror -ggdb3

LIBS		= ../../libft/libft.a ../../MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

all :	$(NAMEBONUS)

.c.o :
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $(<:.c=.o)

$(NAMEBONUS) : $(OBJSBONUS)
	$(MAKE) -C ../../libft
	$(CC) $(CFLAGS) $(HEAD) $(OBJSBONUS) $(LIBS) -o ../../$(NAMEBONUS)

debug :
	$(MAKE) -C ../../libft
	$(CC) $(CFLAGS) $(HEAD) -fsanitize=address $(SRCSBONUS) $(LIBS) -o ../../$(NAMEBONUS)

clean :
	$(MAKE) clean -C ../../libft
	$(RM) $(OBJSBONUS)

fclean :
	$(MAKE) fclean -C ../../libft
	$(RM) $(OBJSBONUS)
	$(RM) ../../$(NAMEBONUS)

re :	fclean all

rebonus : fclean bonus

.PHONY : all clean fclean debug re mlx42 bonus rebonus
