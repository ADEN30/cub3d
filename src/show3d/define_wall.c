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

static void define_WE(t_vars *v, t_point **p, int i)
{
    if (v->pers->x < (*p)[i].x)
        p[0][i].dir = 2;
    else
        p[0][i].dir = 4;
}

static void define_NS(t_vars *v, t_point **p, int i)
{
    if (v->pers->y < (*p)[i].y)
        p[0][i].dir = 1;
    else
        p[0][i].dir = 3;
}

int	define_wall(t_vars *vars)
{
    int         i;
    int         count;
    t_point     **p;

    i = 0;
    count = 0;
    p = &vars->pers->rays[0]->points;
    while (i < vars->pers->rays[0]->n_rays - 1)
    {
        if ((p[0][i].x == p[0][i + 1].x)
            && (p[0][i].y != p[0][i + 1].y))
            define_WE(vars, p, i);
        else if ((p[0][i].y == p[0][i + 1].y)
            && (p[0][i].x != p[0][i + 1].x))
            define_NS(vars, p, i);
        else if ((p[0][i].y == p[0][i + 1].y)
            && (p[0][i].x == p[0][i + 1].x))
           count++;
        else
           p[0][i].dir = 5;
        i++;
    }
    return (vars->pers->rays[0]->n_rays - count);
}
