/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:18:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/21 14:39:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//int    next_point_diff(t_vars *vars, int i)
//{
    //t_point *point;

    //point = vars->pers->rays[0]->points;
    //if (point[i].x)
    //{
        //if (point[i + 1].x)
        //{
            //if ((point[i].x == point[i + 1].x)
                //&& (point[i].y == point[i + 1].y))
                //return (0);
            //else
                //return (1);
        //}
        //else
        //{
            //if ((point[i].x == point[i - 1].x)
                //&& (point[i].y == point[i - 1].y))
                //return (0);
            //else
                //return (1);
        //}
    //}
    //return (0);
//}

static void define_WE(t_vars *vars, int i)
{
    if (vars->pers->x < vars->pers->rays[0]->points[i].x)
        vars->pers->rays[0]->points[i].dir = 'E';
    else
        vars->pers->rays[0]->points[i].dir = 'W';
}

static void define_NS(t_vars *vars, int i)
{
    if (vars->pers->y < vars->pers->rays[0]->points[i].y)
        vars->pers->rays[0]->points[i].dir = 'S';
    else
        vars->pers->rays[0]->points[i].dir = 'N';
}

static void check_last(t_vars *vars, int i)
{
    t_point *point;

    point = vars->pers->rays[0]->points;
    if (point[i].x == point[i - 1].x && point[i].y != point[i - 1].y)
    {
        if (vars->pers->x < point[i].x)
            vars->pers->rays[0]->points[i].dir = 'E';
        else
            vars->pers->rays[0]->points[i].dir = 'W';
    }
    else if (point[i].x != point[i - 1].x && point[i].y == point[i - 1].y)
    {
        if (vars->pers->y < point[i].y)
            vars->pers->rays[0]->points[i].dir = 'S';
        else
            vars->pers->rays[0]->points[i].dir = 'N';
    }
    else
        return ;
}

int	define_wall(t_vars *vars)
{
    int         i;
    int         count;
    t_point     *point;

    i = 0;
    count = 0;
    point = vars->pers->rays[0]->points;
    while (point[i].x)
    {
        if (point[i + 1].x)
        {
            if ((point[i].x == point[i + 1].x)
                && (point[i].y != point[i + 1].y))
                define_WE(vars, i);
            else if ((point[i].y == point[i + 1].y)
                && (point[i].x != point[i + 1].x))
                define_NS(vars, i);
            else
                count++;
        }
        else
            check_last(vars, i);
        //printf("i= %d | dir= %c\n", i, (char)vars->pers->rays[0]->points[i].dir);
        i++;
    }
    return (vars->pers->rays[0]->n_rays - count);
}
