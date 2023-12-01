#include "../../include/cub3d.h"

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
		change_plan(vars);
		create_vue(vars);
		if (&vars->pers->rays[0]->points)
			free(vars->pers->rays[0]->points);

	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) || mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->y = vars->pers->y + 10;
		change_plan(vars);
		create_vue(vars);
		if (&vars->pers->rays[0]->points)
			free(vars->pers->rays[0]->points);

	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->x = vars->pers->x - 10;
		change_plan(vars);
		create_vue(vars);
		if (&vars->pers->rays[0]->points)
			free(vars->pers->rays[0]->points);

	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->pers->x = vars->pers->x + 10;
		change_plan(vars);
		create_vue(vars);
		if (&vars->pers->rays[0]->points)
			free(vars->pers->rays[0]->points);

	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->turn += 1;	
		change_plan(vars);
		create_vue(vars);
		if (&vars->pers->rays[0]->points)
			free(vars->pers->rays[0]->points);

	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
		vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
		vars->turn -= 1 ;	
		change_plan(vars);
		create_vue(vars);
		if (&vars->pers->rays[0]->points)
			free(vars->pers->rays[0]->points);

	}
	
}
