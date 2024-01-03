#include "../../include/cub3d.h"

void	clear_pixel(t_ray **ray)
{
	ray[0]->img->instances[ray[0]->img->count - 1].enabled = 0;
}

void	rotate_left(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	vars->pers->angle += (1 * M_PI / 180);
	if (vars->pers->angle < 0)
		vars->pers->angle =  2 * M_PI + vars->pers->angle;
	if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
    vars->pers->deltax = cos(vars->pers->angle);
    vars->pers->deltay = sin(vars->pers->angle);
	find_wall(vars);
	show_view(vars);
}

void	rotate_right(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	vars->pers->angle -= (1 * M_PI / 180);
	if (vars->pers->angle < 0)
		vars->pers->angle =  2 * M_PI + vars->pers->angle;
	if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
    vars->pers->deltax = cos(vars->pers->angle);
    vars->pers->deltay = sin(vars->pers->angle);
	find_wall(vars);
	show_view(vars);
}
