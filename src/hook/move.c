#include "../../include/cub3d.h"

void	move_a(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	if (vars->pers->angle < 0)
		vars->pers->angle =  2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->x = vars->pers->x + cos(vars->pers->angle + (90 * M_PI / 180));
	vars->pers->y = vars->pers->y - sin(vars->pers->angle + (90 * M_PI / 180));
	find_wall(vars);
	show_view(vars);
}

void	move_d(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	if (vars->pers->angle < 0)
		vars->pers->angle =  2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle -=  2 * M_PI;
	vars->pers->x = vars->pers->x - cos(vars->pers->angle + (90 * M_PI / 180));
	vars->pers->y = vars->pers->y + sin(vars->pers->angle + (90 * M_PI / 180));
	find_wall(vars);
	show_view(vars);
}

void	move_w(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	if (vars->pers->angle < 0)
		vars->pers->angle =  2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->x = vars->pers->x + vars->pers->deltax;
	vars->pers->y = vars->pers->y - vars->pers->deltay;
	find_wall(vars);
	show_view(vars);
}

void	move_s(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	if (vars->pers->angle < 0)
		vars->pers->angle =  2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->x = vars->pers->x - vars->pers->deltax;
	vars->pers->y = vars->pers->y + vars->pers->deltay;
	find_wall(vars);
	show_view(vars);
}

void	ft_move(void* param)
{
	t_vars *vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP) || mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move_w(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) || mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move_s(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		move_a(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		move_d(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars);
}
