/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:18:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/27 17:02:04 by agallet          ###   ########.fr       */
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

static int define_value(t_vars *v, int i, int *j, int *count)
{
    *j = i + 1;
    while (v->pers->rays[0]->points[i].x == v->pers->rays[0]->points[*j].x
        && v->pers->rays[0]->points[i].y == v->pers->rays[0]->points[*j].y)
    {
        (*j)++;
        (*count)++;
    }
    //printf("i = %d j = %d\n", i, *j);
    //printf("X= %d / %d | Y= %d / %d\n", (int)v->pers->rays[0]->points[i].x, (int)v->pers->rays[0]->points[*j].x, (int)v->pers->rays[0]->points[i].y, (int)v->pers->rays[0]->points[*j].y);
    if (*j >= v->pers->rays[0]->length)
        return (-1);
    return (*j);
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

//static void check_last(t_vars *v, t_point **p, int i, int j)
//{
    //if (((int)p[0][i].x == (int)p[0][j].x)
        //&& ((int)p[0][i].y != (int)p[0][j].y))
    //{
        //if (v->pers->x < (*p)[i].x)
            //p[0][j].dir = 2;
        //else
            //p[0][j].dir = 4;
    //}
    //else if (((int)p[0][i].y == (int)p[0][j].y)
        //&& ((int)p[0][i].x != (int)p[0][j].x))
    //{
        //if (v->pers->y < (*p)[i].y)
            //p[0][j].dir = 1;
        //else
            //p[0][j].dir = 3;
    //}
//}

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
		 if ((p[0][i].y != p[0][j].y)
            && (p[0][i].x != p[0][j].x))
            compensate_value(vars, i, j);
        if (((p[0][i].x == p[0][j].x)
            && (p[0][i].y != p[0][j].y))
            || ((p[0][i].y == p[0][j].y)
            && (p[0][i].x != p[0][j].x)))
                define_NESW(vars, p, i, j);
        //printf("dir = %d\n", vars->pers->rays[0]->points[i].dir);
        i = j;
    }
	
	printf("count: %d\n", count);
    return (vars->pers->rays[0]->length - count);
}
