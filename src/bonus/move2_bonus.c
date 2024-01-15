/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:30:51 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/14 15:49:44 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_before_collision(t_vars *vars, double *adjust, double x,
	double y)
{
	if (((int) adjust[0] / vars->dim != (int) x / vars->dim)
		&& ((int) adjust[1] / vars->dim != (int) y / vars->dim))
	{
		if ((vars->map->tab[(int) y / vars->dim][(int) adjust[0]
				vars->dim]) == '1' && (vars->map->tab[(int) adjust[1]
				vars->dim][(int) x / vars->dim]) == '1')
			return (1);
	}
	return (0);
}

int	check_collision(t_vars *vars, double x, double y)
{
	double	adjust[2];

	adjust[0] = vars->pers->x;
	adjust[1] = vars->pers->y;
	if (check_before_collision(vars, adjust, x, y))
		return (1);
	if (vars->map->tab[(int) y / vars->dim][(int) x / vars->dim] == '1')
	{
		if (vars->map->tab[(int) adjust[1] / vars->dim][(int) x
			/ vars->dim] != '1')
			adjust[0] = x;
		if (vars->map->tab[(int) y / vars->dim][(int) adjust[0]
			/ vars->dim] != '1')
			adjust[1] = y;
		if (adjust[0] == vars->pers->x && adjust[1] == vars->pers->y)
			return (1);
		vars->pers->x = adjust[0];
		vars->pers->y = adjust[1];
	}
	else
	{
		vars->pers->x = x;
		vars->pers->y = y;
	}
	return (0);
}

static void	rotate_left(t_vars *vars)
{
	vars->pers->angle += (1 * M_PI / 180);
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->deltax = cos(vars->pers->angle);
	vars->pers->deltay = sin(vars->pers->angle);
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	show_view(vars);
	show_minimap(vars);
	rays_on_minimap(vars);
}

static void	rotate_right(t_vars *vars)
{
	vars->pers->angle -= (1 * M_PI / 180);
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
	vars->pers->deltax = cos(vars->pers->angle);
	vars->pers->deltay = sin(vars->pers->angle);
	if (vars->pers->points)
		free(vars->pers->points);
	find_wall(vars);
	show_view(vars);
	show_minimap(vars);
	rays_on_minimap(vars);
}

void	move2(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars);
}
