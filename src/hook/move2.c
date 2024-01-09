/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:30:51 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/09 13:03:23 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_collision(t_vars *vars, double x, double y)
{
	double	adjust[2];

	adjust[0] = vars->pers->x;
	adjust[1] = vars->pers->y;
	if (x > vars->map->x * MINI - 0.25 || y > vars->map->y * MINI - 0.25
		|| x < 0.25 || y < 0.25)
	{
		if (x > 0.25 && x < vars->map->x * MINI)
			adjust[0] = x;
		if (y > 0.25 && y < vars->map->y * MINI)
			adjust[1] = x;
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
	delete_images(vars);
	show_view(vars);
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
	delete_images(vars);
	show_view(vars);
}

void	move2(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars);
}

void	delete_images(t_vars *vars)
{
	if (vars->style->images->threed)
		mlx_delete_image(vars->mlx, vars->style->images->threed);
	vars->style->images->threed = mlx_new_image(vars->mlx,
			MAX_WIDTH, MAX_HEIGHT);
}
