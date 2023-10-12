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

OBJS	= ${SRCS:.c=.o}

LFT		= libft/libft.a

MLX		= MLX42

HEAD	= -I include -I ${MLX}/include/MLX42 -I libft

NAME	= cub3d

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -D MAP=1

LIBS		= -L ./libft -lft -L ${MLX}/build -lmlx42 -L"/$$HOME/.brew/opt/glfw/lib/" -lglfw 

FRAMEWORK	= -framework Cocoa -framework OpenGL -framework IOKit

.c.o:
		${CC} ${HEAD} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${LFT} ${MLX} ${OBJS}
			${CC} ${HEAD} ${CFLAGS} ${OBJS} ${LIBS} -ldl -pthread -lm -o ${NAME}

${LFT}:
			make -s -C libft

all:		${NAME}


${MLX}:
			@if [ -f ${MLX}/build/libmlx42.a ]; then \
				echo "La libraire est presente"; \
			else \
				cd ${MLX} && cmake -B build && make -s -C build; \
			fi

clean:
			${RM} ${OBJS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all


.PHONY: all clean fclean re
