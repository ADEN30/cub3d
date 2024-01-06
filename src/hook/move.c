/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:10:41 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/06 17:02:11 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_a(t_vars *vars)
{
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->x = vars->pers->x + cos(vars->pers->angle + (90 * M_PI / 180));
	vars->pers->y = vars->pers->y - sin(vars->pers->angle + (90 * M_PI / 180));
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	delete_images(vars);
	rays_on_minimap(vars);
	show_view(vars);
}

void	move_d(t_vars *vars)
{
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle -= 2 * M_PI;
	vars->pers->x = vars->pers->x - cos(vars->pers->angle + (90 * M_PI / 180));
	vars->pers->y = vars->pers->y + sin(vars->pers->angle + (90 * M_PI / 180));
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	delete_images(vars);
	rays_on_minimap(vars);
	show_view(vars);
}

void	move_w(t_vars *vars)
{
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->x = vars->pers->x + vars->pers->deltax;
	vars->pers->y = vars->pers->y - vars->pers->deltay;
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	delete_images(vars);
	rays_on_minimap(vars);
	show_view(vars);
}

void	move_s(t_vars *vars)
{
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->x = vars->pers->x - vars->pers->deltax;
	vars->pers->y = vars->pers->y + vars->pers->deltay;
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	delete_images(vars);
	rays_on_minimap(vars);
	show_view(vars);
}

void	move(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move_w(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move_s(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		move_a(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		move_d(vars);
	move2(vars);
}
