/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:18:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/27 18:38:43 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void define_NESW(t_vars *v, t_point **p, int i, int j)
{
    if (((int)p[0][i].x == (int)p[0][j].x)
        && ((int)p[0][i].y != (int)p[0][j].y))
    {
        if (v->pers->x < (*p)[i].x)
            p[0][i].dir = 2;
        else
            p[0][i].dir = 4;
    }
    else if (((int)p[0][i].y == (int)p[0][j].y)
        && ((int)p[0][i].x != (int)p[0][j].x))
    {
        if (v->pers->y < (*p)[i].y)
            p[0][i].dir = 1;
        else
            p[0][i].dir = 3;
    }
}

static void compensate_value(t_vars *v, int i, int j)
{
    int k;

    k = j;
    while (v->pers->rays[0]->points[j].x == v->pers->rays[0]->points[k].x
        && v->pers->rays[0]->points[j].y == v->pers->rays[0]->points[k].y)
        k++;
    if (v->pers->rays[0]->points[j].x == v->pers->rays[0]->points[k].x)
        v->pers->rays[0]->points[i].x = v->pers->rays[0]->points[j].x;
    if (v->pers->rays[0]->points[j].y == v->pers->rays[0]->points[k].y)
        v->pers->rays[0]->points[i].y = v->pers->rays[0]->points[j].y;
}

int define_value(t_vars *v, int i, int *j, int *count)
{
    *j = i + 1;
    while ((int)v->pers->rays[0]->points[i].x == (int)v->pers->rays[0]->points[*j].x
        && (int)v->pers->rays[0]->points[i].y == (int)v->pers->rays[0]->points[*j].y)
    {
        v->pers->rays[0]->points[*j].x = 0;
        v->pers->rays[0]->points[*j].y = 0;
        v->pers->rays[0]->points[*j].coeff = 0;
        (*j)++;
        (*count)++;
    }
    if (*j >= v->pers->rays[0]->length)
        return (-1);
    return (*j);
}


int	define_wall(t_vars *vars)
{
    int         i;
    int         j;
    int         count;
    t_point     **p;

	i = 0;
    count = 0;
    p = &vars->pers->rays[0]->points;
    while (i < vars->pers->rays[0]->length - 1)
    {
        if (define_value(vars, i, &j, &count) == -1)
            break;
        if (((int)p[0][i].y != (int)p[0][j].y)
            && ((int)p[0][i].x != (int)p[0][j].x))
            compensate_value(vars, i, j);
        if ((((int)p[0][i].x == (int)p[0][j].x)
            && ((int)p[0][i].y != (int)p[0][j].y))
            || (((int)p[0][i].y == (int)p[0][j].y)
            && ((int)p[0][i].x != (int)p[0][j].x)))
                define_NESW(vars, p, i, j);
        i = j;
    } 
    int k = -1;
    while (++k < vars->pers->rays[0]->length)
    {
        if (vars->pers->rays[0]->points[k].x != 0 && vars->pers->rays[0]->points[k].y != 0)
            printf("i = %d | x = %d | y = %d\n", k, (int)vars->pers->rays[0]->points[k].x, (int)vars->pers->rays[0]->points[k].y);
    }
    return (vars->pers->rays[0]->length - count);
}
