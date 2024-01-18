/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:02:56 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/18 21:14:31 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	change_xy(t_vars *vars, int i, double *xy, double dst)
{
	vars->pers->points[i].x = xy[0];
	vars->pers->points[i].y = xy[1];
	vars->pers->points[i].dst = dst;
	vars->pers->points[i].ray = 0;
	vars->pers->points[i].h = 0;
}

static void	define_angle(t_vars *vars)
{
	if (vars->pers->angle < 0)
		vars->pers->angle = 2 * M_PI + vars->pers->angle;
	if (vars->pers->angle > 2 * M_PI)
		vars->pers->angle = vars->pers->angle - 2 * M_PI;
}

static char	check_move(t_vars *vars, double x, double y, int i)
{
	double	h[2];
	double	dst[2];
	double	v[2];
	double	ra;
	char	face[2];

	h[0] = x;
	v[0] = x;
	h[1] = y;
	v[1] = y;
	ra = vars->pers->angle;
	vars->pers->angle = vars->pers->angle + M_PI / 180 * 30;
	define_angle(vars);
	horizontal_intersection(vars, h, face);
	dst[0] = dist(vars, h[0], h[1]);
	vertical_intersection(vars, v, face);
	dst[1] = dist(vars, v[0], v[1]);
	vars->pers->points[i].angle = vars->pers->angle;
	vars->pers->angle = ra;
	check_equal(vars, i, dst);
	if ((dst[0] <= dst[1] && dst[0] != 0) || dst[1] == 0)
		return (change_xy(vars, i, h, dst[0]), face[1]);
	else if ((dst[1] <= dst[0] && dst[1] != 0) || dst[0] == 0)
		return (change_xy(vars, i, v, dst[1]), face[0]);
	return ('0');
}

void	find_wall(t_vars *vars)
{
	int		i;
	double	ratio;

	i = 0;
	vars->pers->points = ft_calloc(sizeof(t_point), MAX_WIDTH);
	if (!vars->pers->points)
	{
		print_error("Error\nCan not print minimap");
		free_vars(vars);
		exit(1);
	}
	ratio = 60 / (double) MAX_WIDTH;
	while (i < MAX_WIDTH)
	{
		vars->pers->points[i].face
			= check_move(vars, vars->pers->x, vars->pers->y, i);
		i++;
		vars->pers->angle -= ratio * M_PI / 180;
	}
	vars->pers->angle = vars->pers->angle + (60 * M_PI / 180);
}
