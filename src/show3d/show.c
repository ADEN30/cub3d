/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:05:36 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/27 18:26:51 by jmathieu         ###   ########.fr       */
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
                get_rgba(103, 52, 71, 255));
            else if (vars->pers->rays[0]->points[i].dir == 1)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(163, 159, 146, 255));
            else if (vars->pers->rays[0]->points[i].dir == 3)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(255, 255, 255, 255));
            else if (vars->pers->rays[0]->points[i].dir == 4)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(0, 0, 0, 255));
        }
        else if (vars->pers->rays[0]->points[i].dir == 5)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(100, 100, 100, 255));
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
    w_height = 32 / (d_wall * 0.0009);
    //printf("percu = %f\n", w_height);
    //usleep(100000);
    return (w_height);
}

static int  calculate_tab_length2(int j)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (i < j)
    {
        count++;
        i++;
    }
    return (count);
} 

static int  calculate_tab_length(int i1, int i2)
{
    int count;

    count = 0;
    while (i1 < i2)
    {
        count++;
        i1++;
    }
    return (count);
} 

static void init_dim(t_dim *dim, int count)
{
    int i;

    i = 0;
    dim = malloc(sizeof(t_dim) * count);
    while (i < count)
    {
        dim[i].x = 0;
        dim[i].y = 0;
        dim[i].dir = 0;
        i++;
    }
}

static t_dim *create_tab(t_vars *v, t_dim *dim, int count)
{
    int i;
    int j;

	i = 0;
    j = 0;
    while (i < count)
    {
        if (v->pers->rays[0]->points[i].x != 0
            || v->pers->rays[0]->points[i].y != 0)
        {
            dim[j].x = v->pers->rays[0]->points[i].x;
            dim[j].y = v->pers->rays[0]->points[i].y;
            dim[j].dir = v->pers->rays[0]->points[i].dir;
            j++;
        }
        i++;
    }
    return (dim);
}

int value_test(t_vars *v, int i, int *j, int *count)
{
    int k;

    k = 0;
    *j = i + 1;
    while ( *j < v->pers->rays[0]->length
        && (int)v->pers->rays[0]->points[i].x == (int)v->pers->rays[0]->points[*j].x
        && (int)v->pers->rays[0]->points[i].y == (int)v->pers->rays[0]->points[*j].y
        )
    {
        v->pers->rays[0]->points[*j].x = 0;
        v->pers->rays[0]->points[*j].y = 0;
        v->pers->rays[0]->points[*j].coeff = 0;
        (*j)++;
        (*count)++;
        k++;
    }
    if (*j == v->pers->rays[0]->length)
    {
        *j = k;
        return (-1);
    }
    return (*j);
}

static int  calculate_rays(t_vars *v)
{
    int     nb_rays;
    int     i;
    int     j;
    int     count;
    t_dim   *dim;

    i = 0;
    j = 0;
    dim = NULL;
    nb_rays = define_wall(v);
    printf("Nb rays = %d\n", nb_rays);
    count = ft_search(v);
    printf("count = %d\n", count);
    while (i < v->pers->rays[0]->length)
    {
        if (value_test(v, i, &j, &count) == -1)
        {
            count += calculate_tab_length2(j);
            break ;
        }
        else if (((int)v->pers->rays[0]->points[i].x == (int)v->pers->rays[0]->points[j].x))
            count += calculate_tab_length(v->pers->rays[0]->points[i].x, v->pers->rays[0]->points[j].x);
        else if (((int)v->pers->rays[0]->points[i].y == (int)v->pers->rays[0]->points[j].y))
            count += calculate_tab_length(v->pers->rays[0]->points[i].y, v->pers->rays[0]->points[j].y);
        i = j;
    }
    init_dim(dim, count);
    dim = create_tab(v, dim, count);
    if (v->mlx->width % nb_rays != 0)
        return ((v->mlx->width / nb_rays) + 1);
    else
        return (v->mlx->width / nb_rays);
}

void    show_vue(t_vars *vars)
{
    int     i;
    int     j;
    int     x;
    int     count;

    i = vars->mlx->width;
    x = 0;
    count = calculate_rays(vars);
    if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
    while (x < vars->mlx->width)
    {
        if (vars->pers->rays[0]->points[i].dir != 0)
        {
            //printf("x = %d | dir = %d\n", x, vars->pers->rays[0]->points[i].dir);
            j = -1;
            while (++j < count)
                wall_column(vars, x + j, calculate_height(vars, i), i);
            x = x + j;
        }
        i--;
    }
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
    vars->style->images->threed->instances[0].z = 1;
}
