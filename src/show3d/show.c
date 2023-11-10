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

static double	distance2(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

static void wall_column(t_vars *vars, int i, double w_height)
{
    int		c_width;
	double	x_screen;
	double	y_screen;
	int		j = 0;

	c_width = 1;
    x_screen = i * c_width;
    y_screen = ((double)1500 - w_height) / 2;
    while (j < 1500)
    {
        mlx_put_pixel(vars->style->images->img, x_screen, y_screen, 255);
		i++;
    }
}

void	show_vue(void *param)
{
	t_vars	*vars;
	double	*d_wall;
	double	*w_height;
	int		i;

	i = 0;
	vars = param;
	d_wall = NULL;
	w_height = NULL;
	mlx_delete_image(vars->mlx, vars->style->images->img);
	vars->style->images->img = mlx_new_image(vars->mlx, 1500, 1500);
    while (i < vars->pers->rays[0]->n_rays)
    {
		// distance pour chaque pixel entre le joueur et le mur 
		d_wall[i] = distance2((double)vars->pers->x, (double)vars->pers->y,
			vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
        w_height[i] = (32 / d_wall[i]) * 100;
        wall_column(vars, i, w_height[i]);
    }
}
