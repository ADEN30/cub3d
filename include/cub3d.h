#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <memory.h>
# include <math.h>
# include "MLX42.h"
# include "./include/libft.h"

# ifndef MAP
#  define MAP 0
# endif

# ifndef DIMENSION
#  define DIMENSION 32
# endif

# ifndef MAX_RAY
#  define MAX_RAY 200
# endif

typedef struct	s_point {
	int		x;
	int		y;
	bool	enabled;
	double	coeff;
}	t_point;

typedef struct	s_ray {
	mlx_image_t	*img;
	t_point		*points;
	int			count_points;
	int			length;
	int			col_x;
	int			col_y;
	int			distance_proj;
	double		dir;
	double		d1;
	double		d2;
	double		d3;
	double		angle;
	double		teta;
	double		coefdir;
}	t_ray;

typedef struct	s_pers {
	int		y;
	int		x;
	double	orientation;
t_ray	**rays;
	int		ray_length;
}	t_pers;

typedef struct	s_map {
	int		fd;
	t_list	*lines;
}	t_map;

typedef struct	s_images {
	mlx_texture_t	*north_texture;
	mlx_image_t		**north;
	int				count_north;
	mlx_texture_t	*south_texture;
	mlx_image_t		**south;
	int				count_south;
	mlx_texture_t	*west_texture;
	mlx_image_t		**west;
	int				count_west;
	mlx_texture_t	*east_texture;
	mlx_image_t		**east;
	int				count_east;
	mlx_image_t		*floor_image;
	mlx_image_t		*roof_image;
	mlx_image_t		*wall_image;
}	t_images;

typedef struct	s_style {
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				define_floor;
	uint32_t		floor;
	int				define_roof;
	uint32_t	 	roof;
	uint32_t	 	wall;
	t_images		*images;	
}	t_style;

typedef struct	s_vars {
	mlx_t	*mlx;
	t_map	*map;
	t_style	*style;
	t_pers	*pers;
}	t_vars;

/*utils*/
	/*free_all*/
void		free_rays(t_ray **rays, t_vars *vars);
void		free_vars(t_vars *vars);
	/*init struct*/
t_map		*init_map(void);
t_style		*init_style(void);
t_pers		*init_pers(int x, int y, char c, t_vars *vars);
t_ray		**init_ray(t_vars *vars);
t_vars		*init_vars(void);
	/*tools*/
uint32_t	value_rgb(char *line);
char		find_case(t_list *list, int x, int y);
int			print_error(char *str);
int			put_pixels(mlx_image_t *img, uint32_t color);
int			largest_line(t_list *list);

/*map*/
int			create_map(int argc, char *argv[], t_vars *vars);
int			show_map(t_vars *vars);

/*style*/
uint32_t	get_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
int			find_all_style(t_vars *vars, char **line);

/*test*/
int			test_map(t_vars *vars);

/*hook*/
void		ft_hook_move(void* param);
void		change_plan(t_vars* vars);

/*raycasting*/
void		ft_raycasting(void *param);
void	turn_camera(t_vars* vars);

/*show3d*/
int			init_3d(t_vars *vars);
void		show_vue(void *param);

#endif
