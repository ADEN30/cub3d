#include "../../include/cub3d.h"

static int	init(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!(*texture))
		return (1);
	return (0);
}

static int	create_roof_floor(t_vars *vars)
{
	mlx_image_t	*roof;
	mlx_image_t	*floor;

	/*Creation des images*/
	roof = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height / 2);
	if (!roof)
		return (1);
	vars->style->images->roof_image = roof;
	floor = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height / 2);
	if (!floor)
		return (1);
	vars->style->images->floor_image = floor;

	/*Affichage des images*/
	if (mlx_image_to_window(vars->mlx, roof, 0, 0) == -1)
		return (1);
	if (put_pixels(roof, vars->style->roof))
		return (1);
	if (mlx_image_to_window(vars->mlx, floor, 0, vars->mlx->height / 2) == -1)
		return (1);
	if (put_pixels(floor, vars->style->floor))
		return (1);
	return (0);
}

int	init_3d(t_vars *vars)
{
	t_images	*imgs;
	t_style		*style;

	style = vars->style;
	imgs = style->images;
	if (MAP == 0)
	{
		if (init(style->north_path, &imgs->north_texture)
			|| init(style->south_path, &imgs->south_texture)
			|| init(style->west_path, &imgs->west_texture)
			|| init(style->east_path, &imgs->east_texture))
			return (1);
		if (create_roof_floor(vars))
			return (1);
	}
	//printf("show vue\n");
	return (0);
}
