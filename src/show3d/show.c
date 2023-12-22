/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:05:36 by jmathieu          #+#    #+#             */
/*   Updated: 2023/12/22 18:03:23 by jmathieu         ###   ########.fr       */
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

void select_color(char c, t_vars* vars, int x, int y)
{
	if (c == 'e')
		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(0, 0, 0, 255));
	else if (c == 'o')
 		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(103, 52, 71, 255));
	else if (c == 's')
 		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(163, 159, 146, 255));
	else if (c == 'n')
		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(255, 255, 255, 255));
}

void	draw_height(t_vars* vars, double height, int x, char c)
{
	int	y;
	int start;
	int	save;
	
	start = (vars->mlx->height - height) / 2;
	y = start;
	//int i = vars->mlx->height;
	//while (i-- > vars->mlx->height - height / 2)
		//mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(100, 150, 255, 255));
	save = x;
	while (x < save + 1500 / 600)
	{
		y = start;
		while (y < height + start)
		{
			select_color(c, vars, x, y);
			y++;
		}
		x++;
	}
}

void	create_vue(t_vars* vars)
{
	int	x;
	int	i;
	double	height;
	char	c;
	
	x = 0;
	i = 0;
	if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	while (x < vars->mlx->width)
	{
		while (i < 600)
		{
			height = calculate_height(vars, i);
			c = vars->pers->rays[0]->points[i].a;
			draw_height(vars, height, x * (1500 / 600), c);
			i++;
			break ;
		}
		x++;
	}
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
}
