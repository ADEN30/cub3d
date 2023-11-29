/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:05:36 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/29 17:23:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char  check_dir(int i1, int i2, char c)
{
    if (c == 0)
    {
        if (i1 > i2)
            return ('e');
        else
            return ('o');
    }
    else
    {
        if (i1 > i2)
            return ('s');
        else
            return ('n');
    }
}

char	define_wall(t_vars *vars, int i)
{
    if ((int)vars->pers->rays[0]->points[i].x % 32 == 0
        || (int)(vars->pers->rays[0]->points[i].x + 1) % 32 == 0)
        return (check_dir(vars->pers->rays[0]->points[i].x, vars->pers->x, 0));
    else if ((int)vars->pers->rays[0]->points[i].y % 32 == 0
        || (int)(vars->pers->rays[0]->points[i].y + 1) % 32 == 0)
        return (check_dir(vars->pers->rays[0]->points[i].y, vars->pers->y, 1));
    return (0);
}

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
		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(103, 52, 71, 255));
	else if (c == 'o')
 		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(163, 159, 146, 255));
	else if (c == 's')
 		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(0, 0, 0, 255));
	else if (c == 'n')
		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(255, 255, 255, 255));
}

void	draw_height(t_vars* vars, double height, int x, int i)
{
	int	y;
	int start;
	
	start = (vars->mlx->width - height) / 2;
	y = start;
	while (y < height + start)
	{
		select_color(define_wall(vars, i), vars, x, y);
		y++;
	}
}

char	select_face(int face)
{
	static int	save;

	save = face;
	//if (face != 0)
		//printf("face : %d\n", face);
	if (face == 0)
		return ('e');
	else if (face == 1)
		return ('s');
	else if (face == 2)
		return ('o');
	else if (face == 3)
		return ('n');	
	else
		return(select_face(save));
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
