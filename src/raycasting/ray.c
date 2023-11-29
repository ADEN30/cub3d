#include "../../include/cub3d.h"

int	test_wall(t_vars* vars, double x, double y, int j)
{
	size_t	i;
	mlx_image_t*	wall;

	i = 0;
	wall = vars->style->images->floor_image;
	while (i < wall->count)
	{
		if ((x >= wall->instances[i].x && x <= wall->instances[i].x + wall->width && y >= wall->instances[i].y && y <= wall->instances[i].y + wall->height))
		{
			if (j > -1)
			{
				vars->pers->rays[0]->points[j].wall_x = wall->instances[i].x;
				vars->pers->rays[0]->points[j].wall_y = wall->instances[i].y;
			}
			return (0);
		}
		i++;
	}
	return (1);

}

void	calc_rot(double* x, double* y, t_vars* vars, double angles)
{
	double	x1;
	double	y1;
	double	angle_rad;
	static	double	d1;
	
	if ( vars->bo == 1)
	{
		d1 = 0.000;
		vars->bo = 0;
	}
	angle_rad = (vars->turn + angles)*(M_PI/180);
	x1 = (vars->pers->x ) + d1 * cos(angle_rad);
	y1 = (vars->pers->y) - d1 * sin(angle_rad);
	*x = x1;
	*y = y1;
	d1 += 1;
}

void	stock(t_vars* vars)
{
	double		x;
	double		y;
	double 		angles;
	int			i;

	angles = 0.00;
	i = 0;
	vars->pers->rays[0]->points = malloc(sizeof(t_point) * vars->pers->rays[0]->length);
	while (angles < 60)
	{
		x = vars->pers->x;
		y = vars->pers->y;
		while (!test_wall(vars, x, y, i) && vars->x >= 0 && vars->x <= vars->mlx->width && y >= 0 && y <= vars->mlx->height)
		{
			vars->pers->rays[0]->points[i].y = y;
			vars->pers->rays[0]->points[i].x = x;
			calc_rot(&x, &y, vars, angles);
		}
		i++;
		vars->bo = 1;
		angles += 0.04;
	}
}

 void	change_plan(t_vars* vars)
{
	double		x;
	double		y;
	double 		angles;
	int			i;

	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	vars->pers->rays[0]->length = 0;
	angles = 0.00000;
	i = -1;
	while (angles < 60)
	{
		x = vars->pers->x;
		y = vars->pers->y;
		while (!test_wall(vars, x, y, i) && vars->x >= 0 && vars->x < vars->mlx->width && y > 0 && y < vars->mlx->height)
		{
			mlx_put_pixel(vars->pers->rays[0]->img, x, y,  get_rgba(255, 0, 0, 255));
			calc_rot(&x, &y, vars, angles);
		}
		vars->bo = 1;
		vars->pers->rays[0]->length++;
		angles += 0.04;
	}
	stock(vars);
}
