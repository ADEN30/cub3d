/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vh_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:19:10 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/10 14:26:54 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	never_vh(t_vars *vars, double *r)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
}

int	wall_vh(t_vars *vars, double *r, double *xy, int *mp)
{
	if (mp[0] >= 0 && mp[0] <= vars->map->x
		&& mp[1] >= 0 && mp[1] <= vars->map->y
		&& (int) vars->map->tab[mp[1]][mp[0]] == '1')
	{
		xy[0] = r[0];
		xy[1] = r[1];
		return (1);
	}
	return (0);
}

void	find_wall_vh(t_vars *vars, double *xy, double *ray, double *ofs)
{
	int	i;
	int	mp[2];

	i = 0;
	while (i < max_xy(vars->map->x, vars->map->y))
	{
		mp[0] = (int)ray[0] / vars->dim;
		mp[1] = (int)ray[1] / vars->dim;
		if (mp[0] >= vars->map->x || mp[1] >= vars->map->y
			|| mp[0] < 0 || mp[1] < 0)
		{
			xy[0] = vars->pers->x;
			xy[1] = vars->pers->y;
			return ;
		}
		if (wall_vh(vars, ray, xy, mp))
			return ;
		else
		{
			ray[0] += ofs[0];
			ray[1] += ofs[1];
			i += 1;
		}
	}
}
