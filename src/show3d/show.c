/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:05:36 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/29 16:56:33 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void    wall_column(t_vars *vars, int x, double w_height, int i)
{
    int     j;

    j = -1;
    while (++j < vars->mlx->height)
    {
        if (j > (vars->mlx->height / 2 - (w_height / 2))
            && j < (vars->mlx->height / 2 + (w_height / 2)))
        {
            if (vars->pers->rays[0]->points[i].dir == 2)
                mlx_put_pixel(vars->style->images->threed, x, j,
                get_rgba(0, 255, 0, 255));
            else if (vars->pers->rays[0]->points[i].dir == 1)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(0, 0, 255, 255));
            else if (vars->pers->rays[0]->points[i].dir == 3)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(255, 0, 0, 255));
            else if (vars->pers->rays[0]->points[i].dir == 4)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(100, 100, 100, 255));
            else if (vars->pers->rays[0]->points[i].dir == 0)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(0, 0, 0, 255));
        }
    }
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
    w_height = 50 / (d_wall * 0.0009);
    return (w_height);
}

static void correct_dir(t_vars **v, int i)
{
    if (i + 1 <= (*v)->mlx->width)
    {
        if ((*v)->pers->rays[0]->points[i + 1].dir != (*v)->pers->rays[0]->points[i].dir)
        {
            if ((int)(*v)->pers->rays[0]->points[i + 1].x == (int)(*v)->pers->rays[0]->points[i].x
                && (int)(*v)->pers->rays[0]->points[i + 1].y == (int)(*v)->pers->rays[0]->points[i].y)
                (*v)->pers->rays[0]->points[i].dir = (*v)->pers->rays[0]->points[i + 1].dir;
        }
    }
}

void    show_vue(t_vars *vars)
{
    int     i;
    int     x;

    i = vars->mlx->width - 1;
    x = -1;
    if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
    while (++x < vars->mlx->width)
    {
        correct_dir(&vars, i);
		//printf("x= %d %f %f\n", x, vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
        wall_column(vars, x, calculate_height(vars, i), i);
        i--;
    }
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
    vars->style->images->threed->instances[0].z = 1;
}
