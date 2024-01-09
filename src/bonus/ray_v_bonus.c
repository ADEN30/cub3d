/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_v_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:19:05 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 16:01:54 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	looking_left(t_vars *vars, double *r, double *ofs, char *face)
{
	double	tg;

	tg = tan(vars->pers->angle);
	r[0] = (((int)vars->pers->x / MINI) * MINI) - 0.0001;
	ofs[0] = -MINI;
	if (vars->pers->angle == M_PI / 2)
	{
		r[1] = vars->pers->y;
		ofs[1] = 0;
	}
	else
	{
		r[1] = (vars->pers->x - r[0]) * tg + vars->pers->y;
		ofs[1] = -ofs[0] * tg;
	}
	face[0] = 'W';
}

static void	looking_right(t_vars *vars, double *r, double *ofs, char *face)
{
	double	tg;

	tg = tan(vars->pers->angle);
	r[0] = (((int)vars->pers->x / MINI) * MINI) + MINI;
	ofs[0] = MINI;
	if (vars->pers->angle == M_PI / 2)
	{
		r[1] = vars->pers->y;
		ofs[1] = 0;
	}
	else
	{
		r[1] = (vars->pers->x - r[0]) * tg + vars->pers->y;
		ofs[1] = -ofs[0] * tg;
	}
	face[0] = 'E';
}

void	vertical_intersection(t_vars *vars, double *v, char *face)
{
	double	ray[2];
	double	ofs[2];

	init_tabs(ray, ofs);
	if (vars->pers->angle == M_PI / 2 || vars->pers->angle == 3 * M_PI / 2)
	{
		never_vh(vars, ray);
		return ;
	}
	else if (vars->pers->angle > M_PI / 2 && vars->pers->angle < 3 * M_PI / 2)
		looking_left(vars, ray, ofs, face);
	else if (vars->pers->angle < M_PI / 2 || vars->pers->angle > 3 * M_PI / 2)
		looking_right(vars, ray, ofs, face);
	find_wall_vh(vars, v, ray, ofs);
}
