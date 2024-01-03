#include "../../include/cub3d.h"

static int	init(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!(*texture))
		return (1);
	return (0);
}

int	init_textures(t_vars *vars)
{
	t_images	*imgs;
	t_style		*style;

	style = vars->style;
	imgs = style->images;
	vars->style->images->threed = NULL;
	if (init(style->north_path, &imgs->north_texture)
		|| init(style->south_path, &imgs->south_texture)
		|| init(style->west_path, &imgs->west_texture)
		|| init(style->east_path, &imgs->east_texture))
		return (1);
	return (0);
}

int	init_player_textures(t_vars *vars)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	while (++y < vars->map->Y)
	{
		x = -1;
		while (++x < vars->map->X)
		{
			c = (char)vars->map->tab[y][x];
			if (ft_strchr("NSEW", c))
			{
				vars->pers = init_pers(x * DIMENSION + (DIMENSION / 2),
				y * DIMENSION + (DIMENSION / 2), c, vars);
			}
		}
	}
	init_textures(vars);
    vars->pers->deltax = cos(vars->pers->angle);
    vars->pers->deltay = sin(vars->pers->angle);
	return (0);
}
