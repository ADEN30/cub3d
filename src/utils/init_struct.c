#include "../../include/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->lines = NULL;
	return (map);
}

t_images	*init_images(void)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	if (!images)
		return (NULL);
	images->count_north = 0;
	images->north = NULL;
	images->count_south = 0;
	images->south = NULL;
	images->count_west = 0;
	images->west = NULL;
	images->count_east = 0;
	images->east = NULL;
	images->floor_image = NULL;
	images->roof_image = NULL;
	images->wall_image = NULL;
	images->img = NULL;
	return (images);
}

t_style	*init_style(void)
{
	t_style	*style;

	style = malloc(sizeof(t_style));
	if (!style)
		return (NULL);
	style->images = init_images();
	if (!style->images)
		return (free(style), NULL);
	style->north_path = NULL;
	style->south_path = NULL;
	style->west_path = NULL;
	style->east_path = NULL;
	style->define_floor = 0;
	style->floor = 0;
	style->define_roof = 0;
	style->roof = 0;
	if (MAP == 1)
		style->wall = get_rgba(0, 0, 0, 255);
	else
		style->wall = get_rgba(0, 0, 0, 0);
	return (style);
}

t_ray	**init_ray(t_vars *vars)
{
	t_ray	**rays;

	rays = malloc(sizeof(t_ray *) * (1));
	if (!rays)
		return (NULL);
	rays[0] = malloc(sizeof(t_ray) * (2));
	rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	rays[0]->count_points = 0;
	rays[0]->angle = 0.00;
	rays[0]->coefdir = 0.00;
	rays[0]->a_r1 = 0.00;
	rays[0]->a_r2 = 0.00;
	rays[0]->dir = 0.00;
	rays[0]->d1 = 0.00;
	rays[0]->d2 = 0.00;
	rays[0]->d3 = 0.00;
	rays[0]->n_rays = 0;
	return (rays);
}

t_pers	*init_pers(int x, int y, char c, t_vars *vars)
{
	t_pers	*pers;

	pers = malloc(sizeof(t_pers));
	if (!pers)
		return (NULL);
	pers->x = 0;
	pers->y = 0;
	if (x != -1)
		pers->x = x;
	if (y != -1)
		pers->y = y;
	pers->rays = init_ray(vars);
	pers->ray_length = ft_lstsize(vars->map->lines) > largest_line(vars->map->lines) ?
		ft_lstsize(vars->map->lines) * DIMENSION:
		largest_line(vars->map->lines) * DIMENSION;
	if (c == 'S')
		pers->orientation = 90 * M_PI /180;
	else if (c == 'N')
		pers->orientation = 270 * M_PI /180;
	else if (c == 'E')
		pers->orientation = 0 * M_PI /180;
	else if (c == 'W')
		pers->orientation = 180 * M_PI /180;
	return (pers);
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->map = NULL;
	vars->style = NULL;
	vars->pers = NULL;
	return (vars);
}
