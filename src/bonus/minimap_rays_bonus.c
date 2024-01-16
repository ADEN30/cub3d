/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rays_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:57 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/15 17:16:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	h_error(int *err, int *dxy, int *x0, int *sxy)
{
	err[0] += dxy[1];
	*x0 += sxy[0];
}

static void	v_error(int *err, int *dxy, int *y0, int *sxy)
{
	err[0] += dxy[0];
	*y0 += sxy[1];
}

static void	define_sxy(t_vars *vars, int i, int *sxy)
{
	if (vars->pers->x < vars->pers->points[i].x)
		sxy[0] = 1;
	else
		sxy[0] = -1;
	if (vars->pers->y < vars->pers->points[i].y)
		sxy[1] = 1;
	else
		sxy[1] = -1;
}

static void	drawrays(t_vars *vars, int x0, int y0, int i)
{
	int	dxy[2];
	int	sxy[2];
	int	err[2];

	dxy[0] = abs((int) vars->pers->points[i].x - x0);
	dxy[1] = -abs((int) vars->pers->points[i].y - y0);
	err[0] = dxy[0] + dxy[1];
	define_sxy(vars, i, sxy);
	while (1)
	{
		mlx_put_pixel(vars->style->images->threed, x0 / (vars->dim / 8),
			y0 / (vars->dim / 8), get_rgba(1, 215, 88, 255));
		if (x0 == (int) vars->pers->points[i].x
			&& y0 == (int) vars->pers->points[i].y)
			break ;
		err[1] = 2 * err[0];
		if (err[1] >= dxy[1])
			h_error(err, dxy, &x0, sxy);
		if (err[1] <= dxy[0])
			v_error(err, dxy, &y0, sxy);
	}
}

void	rays_on_minimap(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < MAX_WIDTH)
	{
		drawrays(vars, vars->pers->x, vars->pers->y, i);
		i++;
	}
}
