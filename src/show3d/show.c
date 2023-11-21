#include "../../include/cub3d.h"

static void wall_column(t_vars *vars, int i, double w_height)
{
    int     j;

    j = -1;
    printf("x= %d\n", i);
    while (++j < vars->mlx->height)
    {
        if (j > (vars->mlx->height / 2 - (w_height / 2))
            && j < (vars->mlx->height / 2 + (w_height / 2)))
        {
            if (vars->pers->rays[0]->points[i].dir == 'E')
                mlx_put_pixel(vars->style->images->img, i, j, get_rgba(103, 52, 71, 255));
            else if (vars->pers->rays[0]->points[i].dir == 'N')
                mlx_put_pixel(vars->style->images->img, i, j, get_rgba(0, 0, 0, 255));
            if (vars->pers->rays[0]->points[i].dir == 'S')
                mlx_put_pixel(vars->style->images->img, i, j, get_rgba(163, 159, 146, 255));
            else if (vars->pers->rays[0]->points[i].dir == 'W')
                mlx_put_pixel(vars->style->images->img, i, j, get_rgba(0, 0, 0, 255));
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

void    show_vue(void *param)
{
    t_vars  *v;
    int     i;
    int     j;
    int     count;
    int     k; 

    i = 0;
    j = 0;
    v = param;
    count = calculate_rays(v);
    if (v->style->images->img)
        mlx_delete_image(v->mlx, v->style->images->img);
    v->style->images->img = mlx_new_image(v->mlx, v->mlx->width,
        v->mlx->height);
    while (j < 50 /*v->mlx->width*/)
    {
        //printf("dir = %d\n", v->pers->rays[0]->points[i].dir);
        if (v->pers->rays[0]->points[i].dir != 0)
        {
            k = 0;
            //printf("i= %d\n", i);
            while (k < count && j < 50 /*v->mlx->width*/)
            {
                wall_column(v, j, calculate_height(v, i));
                //printf("j= %d | k= %d\n", j, k);
                j++;
                k++;
            }
        }
            i++;
    }
    mlx_image_to_window(v->mlx, v->style->images->img, 0, 0);
    v->style->images->img->instances[0].z = 1;
}
