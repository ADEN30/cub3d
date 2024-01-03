#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <memory.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

# ifndef DIMENSION
#  define DIMENSION 16
# endif

# ifndef FOV
#  define FOV 60
# endif

# ifndef MAX_RAY
#  define MAX_RAY 200
# endif

typedef struct	s_point {
	double		x;
	double		y;
	bool		enabled;
	double		wall_x;
	double		wall_y;
	double		angle;
	char		a;
}	t_point;

typedef struct	s_ray {
	mlx_image_t	*img;
	t_point		*points;
	double		angle;
}	t_ray;

typedef struct	s_pers {
	double			y;
	double			x;
	double		angle;
	double		deltax;
	double		deltay;
	t_ray		**rays;
}	t_pers;

typedef struct	s_map {
	int		fd;
	t_list	*lines;
	int		**tab;
	char	*face;
	int		X;
	int		Y;
}	t_map;

typedef struct	s_images {
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	mlx_image_t		*wall_image;
	mlx_image_t		*threed;
}	t_images;

typedef struct	s_style {
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				define_floor;
	int				define_roof;
	uint32_t		floor;
	uint32_t	 	roof;
	uint32_t	 	wall;
	t_images		*images;	
}	t_style;

typedef struct	s_vars {
	mlx_t	*mlx;
	t_map	*map;
	t_style	*style;
	t_pers	*pers;
	double	turn;
	int	x;
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
int			line_isprint(char *line);
int			check_line(char *line);
uint32_t	value_rgb(char *line, t_vars *vars);
int			put_pixels(mlx_image_t *img, uint32_t color);

/*map*/
void		show_minimap(t_vars *vars);
int			create_map(int argc, char *argv[], t_vars *vars);
int			init_player_textures(t_vars *vars);

/*print_error*/
int			print_error(char *str);

/*style*/
uint32_t	get_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
int			find_style(char *line, t_vars *vars, int *check);
int			find_all_style(t_vars *vars, char **line);

/*test*/
int			create_tab(t_vars *vars, char **line, char *argv);
int			check_map(t_vars *vars);

/*hook*/
void		ft_move(void* param);
void		rotate_left(t_vars *vars);
void		rotate_right(t_vars *vars);
void		clear_pixel(t_ray **ray);
void		find_wall(t_vars* vars);
void		show_view(t_vars *vars);

/*show3d*/
int			define_wall(t_vars *vars);
void 		display_tpoint(t_point* tab, int size);
uint32_t	get_pixel(t_vars *vars, int w_height, int y, int i);

/* raycasting*/
void		never_vh(t_vars *vars, double *r);
void		find_wall_vh(t_vars *vars, double *xy, double *ray, double *ofs);
int			max_xy(int x, int y);
double		dist(t_vars *vars, double x, double y);
void		init_tabs(double *r, double *ofs);
void		horizontal_intersection(t_vars *vars, double *h, char *face);
void		vertical_intersection(t_vars *vars, double *v, char *face);

#endif
