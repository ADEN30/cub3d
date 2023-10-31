#include "../../include/cub3d.h"

//void	move(t_vars *vars, int direction)
//{
	//t_pers *pers = vars->pers;
	//double	angle_rad;
	//int		test[2];
	
	//angle_rad = pers->orientation * M_PI / 180.0;
	//if (direction == 1)
		//angle_rad = (pers->orientation + 180) * M_PI / 180.0;
	//else if (direction == 2)
		//angle_rad = (pers->orientation + 90) * M_PI / 180.0;
	//else if (direction == 3)
		//angle_rad = (pers->orientation + 270) * M_PI / 180.0;
	//double dx = (pers->ray_length * 2) * cos(angle_rad);
	//double dy = (pers->ray_length * 2) * sin(angle_rad);

	//int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	//double xIncrement = dx / steps;
	//double yIncrement = dy / steps;

	//double x1 = pers->x;
	//double y1 = pers->y;
	//test[0] = xIncrement < 0 ?
		//floor(xIncrement) - 1 + pers->x:
		//ceil(xIncrement) + 1 + pers->x;
	//test[1] = yIncrement < 0 ?
		//floor(yIncrement) - 1 + pers->y:
		//ceil(yIncrement) + 1 + pers->y;
	//if (find_case(vars->map->lines, test[0] / DIMENSION, test[1] / DIMENSION) != '1')
	//{
		//x1 += xIncrement * 100 * vars->mlx->delta_time;
		//y1 += yIncrement * 100 * vars->mlx->delta_time;
		//pers->x = round(x1);
		//pers->y = round(y1);
	//}
//}

void	clear_pixel(t_ray **ray)
{
	ray[0]->img->instances[ray[0]->img->count - 1].enabled = 0;
}

void	ft_hook_move(void* param)
{
	t_vars *vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP) || mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->y = vars->pers->y - 10;
		ft_raycasting(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) || mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->y = vars->pers->y + 10;
		ft_raycasting(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->x = vars->pers->x - 10;
		ft_raycasting(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->x = vars->pers->x + 10;
		ft_raycasting(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		change_plan(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		turn_camera(vars);	
}
