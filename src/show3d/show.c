#include "../../include/cub3d.h"

static int wall_column(t_vars *vars, int i, double w_height, int count)
{
    int     j;
    int     k;

    k = -1;
    j = -1;
    while (++k < count)
    {
        while (++j < vars->mlx->height)
        {
            printf("avant\n");
            printf("i = %d\n", i);
            printf("dir = %d\n", vars->pers->rays[0]->points[i].dir);
            printf("apres\n");
            if (j > (vars->mlx->height / 2 - (w_height / 2))
                && j < (vars->mlx->height / 2 + (w_height / 2)))
            {
                //if (vars->pers->rays[0]->points[i].dir == 2)
                    //mlx_put_pixel(vars->style->images->img, i + k, j, get_rgba(103, 52, 71, 255));
                //else if (vars->pers->rays[0]->points[i].dir == 1)
                    //mlx_put_pixel(vars->style->images->img, i + k, j, get_rgba(0, 0, 0, 255));
                //else if (vars->pers->rays[0]->points[i].dir == 3)
                    //mlx_put_pixel(vars->style->images->img, i + k, j, get_rgba(163, 159, 146, 255));
                //else if (vars->pers->rays[0]->points[i].dir == 4)
                    //mlx_put_pixel(vars->style->images->img, i + k, j, get_rgba(0, 0, 0, 255));
                //else
                    mlx_put_pixel(vars->style->images->img, i + k, j, get_rgba(0, 0, 0, 255));
            }
        }
        j = -1;
    }
    return (i + count);
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
    int     count;

    i = 0;
    j = 0;
    count = calculate_rays(vars);
    if (vars->style->images->img)
        mlx_delete_image(vars->mlx, vars->style->images->img);
    vars->style->images->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
    while (j < vars->mlx->width && i < vars->pers->rays[0]->n_rays)
    {
        //printf("bonjour\n");
        //printf("i= %d\n", i);
        if ( vars->pers->rays[0]->points[i].dir != 0)
        {
            //printf("rebonjour\n");
            //printf("x= %d\n", j);
            //printf("j=%d | dir = %d\n", j, vars->pers->rays[0]->points[i].dir);
            j = wall_column(vars, j, calculate_height(vars, i), count);
            //printf("j= %d\n", j);
            //printf("semi-revoir\n");
        }
        i++;
        //printf("aurevoir\n");
    }
    mlx_image_to_window(vars->mlx, vars->style->images->img, 0, 0);
    vars->style->images->img->instances[0].z = 1;
}
