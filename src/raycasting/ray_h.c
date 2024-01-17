/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_h.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:19:00 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/17 11:52:10 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	looking_up(t_vars *vars, double *r, double *ofs, char *face)
{
	double	tg;

	tg = 1 / tan(vars->pers->angle);
	r[1] = (int)vars->pers->y - 0.0001;
	ofs[1] = -1;
	if (vars->pers->angle == M_PI / 2)
	{
		r[0] = vars->pers->x;
		ofs[0] = 0;
	}
	else
	{
		r[0] = (vars->pers->y - r[1]) * tg + vars->pers->x;
		ofs[0] = -ofs[1] * tg;
	}
	face[1] = 'N';
}

static void	looking_down(t_vars *vars, double *r, double *ofs, char *face)
{
	double	tg;

	tg = 1 / tan(vars->pers->angle);
	r[1] = (int)vars->pers->y  + 1;
	ofs[1] = 1;
	if (vars->pers->angle == 3 * M_PI / 2)
	{
		r[0] = vars->pers->x;
		ofs[0] = 0;
	}
	else
	{
		r[0] = (vars->pers->y - r[1]) * tg + vars->pers->x;
		ofs[0] = -ofs[1] * tg;
	}
	face[1] = 'S';
}

int	horizontal_intersection(t_vars *vars, double *h, char *face)
{
	double	ray[2];
	double	ofs[2];

	init_tabs(ray, ofs);
	if (vars->pers->angle == 0 || vars->pers->angle == M_PI)
	{
		never_vh(vars, ray);
		return (0);
	}
	else if (vars->pers->angle < M_PI)
		looking_up(vars, ray, ofs, face);
	else if (vars->pers->angle > M_PI)
		looking_down(vars, ray, ofs, face);
	if (find_wall_vh(vars, h, ray, ofs))
		return (1);
	return (0);
}
