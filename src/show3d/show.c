#include "../../include/cub3d.h"

mlx_image_t	*find_wall(t_vars *vars, t_images **imgs)
{
	mlx_image_t		**img;
	mlx_texture_t	*texture;
	int				i;

	i = 0;
	img = malloc(sizeof(mlx_image_t) * ((*imgs)->count_north + 1));
	if (!img)
		return (NULL);
	texture = (*imgs)->north_texture;
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
	//printf(" %i / %i = %i\n", vars->mlx->height, ray->length, size);
	y = vars->mlx->height / 2 - size / 2;
	mlx_resize_image(wall, 1, size);
	if (mlx_image_to_window(vars->mlx, wall, x, y) == -1)
		return (1);
	return (0);
}

double	distance2(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void	show_vue(void *param)
{
	//t_vars	*vars;
	//t_ray	**rays;
	//int		i = 0;

	//vars = param;
	//rays = vars->pers->rays;
	//print_wall_3d(vars, i, rays[i]);
	//while (rays[i])
	//{
		//print_wall_3d(vars, i, rays[i]);
		//i++;
	//}
	t_vars	*vars;
	double	d_wall;
	double	new_d;

	vars = param;
	//fprintf(stderr, "vars->pers->x = %d\n", vars->pers->x);
	//fprintf(stderr, "vars->pers->y = %d\n", vars->pers->y);
	//fprintf(stderr, "mur->x = %f\n", vars->pers->rays[0]->points[0].x);
	//fprintf(stderr, "mur->y = %f\n", vars->pers->rays[0]->points[0].y);
	d_wall = distance2((double)vars->pers->x, (double)vars->pers->y,
		vars->pers->rays[0]->points[0].x, vars->pers->rays[0]->points[0].y);
	printf("Distance : %f\n", d_wall);	
	new_d = d_wall / 32;
	printf("D * 32: %f\n", new_d);	

}
