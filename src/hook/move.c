/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:10:41 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/15 17:19:04 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	move_a(t_vars *vars)
{
	double	xy[2];

	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	xy[0] = vars->pers->x + cos(vars->pers->angle + (90 * M_PI / 180))
		* vars->spd;
	xy[1] = vars->pers->y - sin(vars->pers->angle + (90 * M_PI / 180))
		* vars->spd;
	if (check_collision(vars, xy[0], xy[1]))
		return ;
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	show_view(vars);
}

static void	move_d(t_vars *vars)
{
	double	xy[2];

	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle -= 2 * M_PI;
	xy[0] = vars->pers->x - cos(vars->pers->angle + (90 * M_PI / 180))
		* vars->spd;
	xy[1] = vars->pers->y + sin(vars->pers->angle + (90 * M_PI / 180))
		* vars->spd;
	if (check_collision(vars, xy[0], xy[1]))
		return ;
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	show_view(vars);
}

static void	move_w(t_vars *vars)
{
	double	xy[2];

	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	xy[0] = vars->pers->x + vars->pers->deltax * vars->spd;
	xy[1] = vars->pers->y - vars->pers->deltay * vars->spd;
	if (check_collision(vars, xy[0], xy[1]))
		return ;
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	show_view(vars);
}

static void	move_s(t_vars *vars)
{
	double	xy[2];

	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	else if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	xy[0] = vars->pers->x - vars->pers->deltax * vars->spd;
	xy[1] = vars->pers->y + vars->pers->deltay * vars->spd;
	if (check_collision(vars, xy[0], xy[1]))
		return ;
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
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
