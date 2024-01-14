/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:54:46 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/14 16:54:09 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <memory.h>
# include <math.h>
# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/include/libft.h"

# ifndef MAX_WIDTH
#  define MAX_WIDTH 800
# endif

# ifndef MAX_HEIGHT
#  define MAX_HEIGHT 600
# endif

# ifndef FOV
#  define FOV 60
# endif

typedef struct s_point {
	double		x;
	double		y;
	double		dst;
	double		h;
	double		angle;
	int			ray;
	char		face;
}	t_point;

typedef struct s_pers {
	double			y;
	double			x;
	double			angle;
	double			deltax;
	double			deltay;
	t_point			*points;
}	t_pers;

typedef struct s_map {
	int		fd;
	int		**tab;
	int		**cp_tab;
	int		x;
	int		y;
}	t_map;

typedef struct s_images {
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	mlx_image_t		*threed;
}	t_images;

typedef struct s_style {
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				define_floor;
	int				define_roof;
	uint32_t		floor;
	uint32_t		roof;
	t_images		*images;	
}	t_style;

typedef struct s_vars {
	mlx_t	*mlx;
	t_map	*map;
	t_style	*style;
	t_pers	*pers;
	int		dim;
	double	spd;
	double	ratio;
}	t_vars;

/*error*/
	/*print_error*/
int			print_error(char *str);

/*hook*/
	/*mouse*/
void		mouse(void *param);
	/*move*/
void		move(void *param);
	/*move2*/
int			check_collision(t_vars *vars, double x, double y);
void		move2(t_vars *vars);
void		delete_images(t_vars *vars);

/*map*/
	/*create_tab*/
int			create_tab(t_vars *vars, char *argv);
	/*init_graphic*/
int			init_graphic(t_vars *vars);
	/*init_graphic2*/
int			check_dimensions(t_vars *vars);
int			init_textures(t_vars *vars);
	/*parse_map*/
int			parse_map(int argc, char *argv[], t_vars *vars);
	/*parse_map_check*/
int			check_next_line(t_vars *vars, char **line);
int			check_assets(t_vars *vars, char **line);
int			badmap(char *file);
	/*parse_map_check2*/
int			check_map(t_vars *vars);
	/*parse_style*/
int			find_all_style(t_vars *vars, char **line);
	/*parse_style2*/
int			find_style(char *line, t_vars *vars, int *check);
	/*parse_style2*/
uint32_t	define_color(char *line, t_vars *vars);

/*raycasting*/
	/*ray*/
void		find_wall(t_vars *vars);
	/*ray_h*/
void		horizontal_intersection(t_vars *vars, double *h, char *face);
	/*ray_v*/
void		vertical_intersection(t_vars *vars, double *v, char *face);
	/*ray_vh*/
void		never_vh(t_vars *vars, double *r);
void		find_wall_vh(t_vars *vars, double *xy, double *ray, double *ofs);
	/*ray_tools*/
int			max_xy(int x, int y);
double		dist(t_vars *vars, double x, double y);
void		init_tabs(double *r, double *ofs);

/*show3d*/
	/*minimap_rays*/
void		rays_on_minimap(t_vars *vars);
	/*show_minimap*/
void		show_minimap(t_vars *vars);
	/*show_view*/
void		show_view(t_vars *vars);
	/*wall_pixel*/
uint32_t	get_pixel(t_vars *vars, t_point *point, int y);

/*style*/
	/*color*/
uint32_t	get_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

/*utils*/
	/*free_all*/
void		free_vars(t_vars *vars);
	/*init struct*/
t_map		*init_map(void);
t_style		*init_style(void);
t_pers		*init_pers(int x, int y, char c);
t_vars		*init_vars(void);
	/*tools*/
int			line_isprint(char *line);
uint32_t	value_rgb(char *line, t_vars *vars);
int			put_pixels(mlx_image_t *img, uint32_t color);

#endif
