#include "../../include/cub3d.h"

static void wall_column(t_vars *vars, int i, double w_height)
{
    int     j;

    j = -1;
    while (++j < vars->mlx->height)
    {
        if (j > (vars->mlx->height / 2 - (w_height / 2))
            && j < (vars->mlx->height / 2 + (w_height / 2)))
        {
            //if (vars->pers->rays[0]->points[i].dir == 'E')
                //mlx_put_pixel(vars->style->images->img, i, j, 255);
            //else if (vars->pers->rays[0]->points[i].dir == 'N')
                //mlx_put_pixel(vars->style->images->img, i, j, 100);
            if (vars->pers->rays[0]->points[i].dir == 'S')
                mlx_put_pixel(vars->style->images->img, i, j, 100);
            //else if (vars->pers->rays[0]->points[i].dir == 'W')
                //mlx_put_pixel(vars->style->images->img, i, j, 200);
        }
    }
}

void    show_vue(void *param)
{
    t_vars  *vars;
    int     nb_rays;
    double  *d_wall;
    double  *w_height;
    int     i;
    int     j;
    int     count;
    int     k; 

    i = 0;
    j = 0;
    vars = param;
    nb_rays = define_wall(vars);
    if (vars->mlx->width % nb_rays != 0)
        count = (vars->mlx->width / nb_rays) + 1;
    else
        count = (vars->mlx->width / nb_rays);
    printf("%d %d\n", nb_rays, count);
    if (vars->style->images->img)
        mlx_delete_image(vars->mlx, vars->style->images->img);
    vars->style->images->img = mlx_new_image(vars->mlx, vars->mlx->width,
        vars->mlx->height);
    d_wall = malloc(nb_rays * sizeof(double));
    w_height = malloc(nb_rays * sizeof(double));
    if (!d_wall || !w_height)
        mlx_terminate(vars->mlx);
    while (j < vars->mlx->width)
    {
        if (next_point_diff(vars, i))
        {
            d_wall[i] = distance(vars->pers->x, vars->pers->y,
                vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
            w_height[i] = 32 / (d_wall[i] * 0.004);
            k = 0;
            while (k < count && j < vars->mlx->width)
            {
                wall_column(vars, j++, w_height[i]);
                k++;
            }
            i++;
        }
        else
            i++;
    }
    mlx_image_to_window(vars->mlx, vars->style->images->img, 0, 0);
    vars->style->images->img->instances[0].z = 1;
}
