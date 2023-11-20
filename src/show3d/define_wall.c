#include "../../include/cub3d.h"

int    next_point_diff(t_vars *vars, int i)
{
    if (vars->pers->rays[0]->points[i].x && vars->pers->rays[0]->points[i + 1].x)
    {
        if ((vars->pers->rays[0]->points[i].x == vars->pers->rays[0]->points[i + 1].x)
            && (vars->pers->rays[0]->points[i].y == vars->pers->rays[0]->points[i + 1].y))
                return (0);
        else
                return (1);
    }
    return (0);
}

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

int	define_wall(t_vars *vars)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (vars->pers->rays[0]->points[i].x && vars->pers->rays[0]->points[i + 1].x)
    {
        if ((vars->pers->rays[0]->points[i].x == vars->pers->rays[0]->points[i + 1].x)
            && (vars->pers->rays[0]->points[i].y != vars->pers->rays[0]->points[i + 1].y))
            define_WE(vars, i);
        else if ((vars->pers->rays[0]->points[i].y == vars->pers->rays[0]->points[i + 1].y)
            && (vars->pers->rays[0]->points[i].x != vars->pers->rays[0]->points[i + 1].x))
            define_NS(vars, i);
        else
            count++;
        i++;
    }
    return (vars->pers->rays[0]->n_rays - count);
}
