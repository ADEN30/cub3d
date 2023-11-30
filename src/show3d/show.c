/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:05:36 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/30 08:12:07 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

static double   calculate_height(t_vars *vars, int i)
{
    double  d_wall;
    double  w_height;

    d_wall = distance(vars->pers->x, vars->pers->y,
        vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
    w_height = 1500 / (d_wall * 0.1);
    return (w_height);
}

void	draw_height(t_vars* vars, double height, int x, int i)
{
	int	y;

	y = -1;
	define_wall(vars, i);
	while (++y < vars->mlx->height - 1)
    {
        if (y <= vars->mlx->height / 2 - (height / 2))
			mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(100, 150, 255, 255));
        //if (y > (vars->mlx->height / 2 - (height / 2))
            //&& y < (vars->mlx->height / 2 + (height / 2)))
			//mlx_put_pixel(vars->style->images->threed, x, y, get_pixel(vars, height, x, y));
        if (y >= vars->mlx->height / 2 + (height / 2))
			mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(191, 170, 143, 255));
	}
}

void	create_vue(t_vars* vars)
{
	int	x;
	int	i;
	double	height;
	
	x = 0;
	i = vars->mlx->width;
	if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	while (x < vars->mlx->width)
	{
		height = calculate_height(vars, --i);
		draw_height(vars, height, x, i);
		x++;
	}
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
}
