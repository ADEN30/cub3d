#include "../../include/cub3d.h"

static void wall_column(t_vars *vars, int x, double w_height, int i)
{
    int     j;

    j = -1;
    while (++j < vars->mlx->height)
    {
        if (j > (vars->mlx->height / 2 - (w_height / 2))
            && j < (vars->mlx->height / 2 + (w_height / 2)))
        {
            if (vars->pers->rays[0]->points[i].dir == 2)
                mlx_put_pixel(vars->style->images->img, x, j, get_rgba(103, 52, 71, 255));
            else if (vars->pers->rays[0]->points[i].dir == 1)
                mlx_put_pixel(vars->style->images->img, x, j, get_rgba(163, 159, 146, 255));
            else if (vars->pers->rays[0]->points[i].dir == 3)
                mlx_put_pixel(vars->style->images->img, x, j, get_rgba(163, 159, 146, 255));
            else if (vars->pers->rays[0]->points[i].dir == 4)
                mlx_put_pixel(vars->style->images->img, x, j, get_rgba(0, 0, 0, 255));
            else if (vars->pers->rays[0]->points[i].dir == 5)
                mlx_put_pixel(vars->style->images->img, x, j, get_rgba(0, 0, 0, 255));
        }
    }
}

static double   calculate_height(t_vars *vars, int i)
{
    double  d_wall;
    double  w_height;

    d_wall = distance(vars->pers->x, vars->pers->y,
        vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
    w_height = 32 / (d_wall * 0.0009);
    return (w_height);
}

static int  calculate_rays(t_vars *vars)
{
    int     nb_rays;

    nb_rays = define_wall(vars);
    if (vars->mlx->width % nb_rays != 0)
        return ((vars->mlx->width / nb_rays) + 1);
    else
        return (vars->mlx->width / nb_rays);
}

void    show_vue(t_vars *vars)
{
    int     i;
    int     j;
    int     x;
    int     count;

    i = 0;
    x = 0;
    count = calculate_rays(vars);
    if (vars->style->images->img)
        mlx_delete_image(vars->mlx, vars->style->images->img);
    vars->style->images->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
    while (x < vars->mlx->width && i < vars->pers->rays[0]->n_rays)
    {
        if (vars->pers->rays[0]->points[i].dir != 0)
        {
            j = -1;
            while (++j < count)
                wall_column(vars, x + j, calculate_height(vars, i), i);
            x = x + j;
        }
        i++;
    }
    mlx_image_to_window(vars->mlx, vars->style->images->img, 0, 0);
    vars->style->images->img->instances[0].z = 1;
}
