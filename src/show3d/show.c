#include "../../include/cub3d.h"

mlx_image_t	*find_wall(t_vars *vars, t_images **imgs)
{
	mlx_image_t	**img;
	mlx_texture_t	*texture;
	int			i;

	i = 0;
	img = malloc(sizeof(mlx_image_t) * ((*imgs)->count_north + 1));
	texture = (*imgs)->north_texture;
	if (!img)
		return (NULL);
	while (i < (*imgs)->count_north)
	{
		img[i] = (*imgs)->north[i];
		i++;
	}
	(*imgs)->count_north++;
	img[i] = mlx_texture_to_image(vars->mlx, texture);
	if (!img[i])
		return (NULL);
	(*imgs)->north = img;
	return (img[i]);
}

int	print_wall_3d(t_vars *vars, int x, t_ray *ray)
{
	int			size;
	int			y;
	mlx_image_t	*wall;

	wall = find_wall(vars, &vars->style->images);
	size = vars->mlx->height / ray->length;
	printf(" %i / %i = %i\n", vars->mlx->height, ray->length, size);
	y = vars->mlx->height / 2 - size / 2;
	mlx_resize_image(wall, 1, size);
	if (mlx_image_to_window(vars->mlx, wall, x, y))
		return (1);
	return (0);
}

void	show_vue(void *param)
{
	t_vars	*vars;
	t_ray	**rays;
	int		i;

	vars = param;
	rays = vars->pers->rays;
	i = 0;
	printf("show vue\n");
	print_wall_3d(vars, i, rays[i]);
	while (rays[i])
	{
		print_wall_3d(vars, i, rays[i]);
		i++;
	}
}
