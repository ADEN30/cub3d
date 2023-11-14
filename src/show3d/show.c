#include "../../include/cub3d.h"

//static uint32_t   get_pixel_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
//{
    //return (r << 24 | g << 16 | b << 8 | a);
//}

static double   distance2(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

static void wall_column(t_vars *vars, int i, double w_height)
{
    int     j;
    j = -1;
    while (++j < 1500)
    {
        //if (j < 750 - (w_height / 2))
            //mlx_put_pixel(vars->style->images->img, i, j, get_pixel(floor));
        //else if (j > 750 + (w_height / 2))
            //mlx_put_pixel(vars->style->images->img, i, j, get_pixel(roof));
        //else
            //mlx_put_pixel(vars->style->images->img, i, j, get_pixel(wall));
        if (j > ((vars->mlx->height / 2) - (w_height / 2))
            && j < ((vars->mlx->height / 2) + (w_height / 2)))
            mlx_put_pixel(vars->style->images->img, i, j, 190);

    }
}

void    show_vue(void *param)
{
    t_vars  *vars;
    double  *d_wall;
    double  *w_height;
    int     i;

    i = -1;
    vars = param;
    w_height = NULL;
    mlx_delete_image(vars->mlx, vars->style->images->img);
    vars->style->images->img = mlx_new_image(vars->mlx, vars->mlx->width,
        vars->mlx->height);
    if (!vars->style->images->img)
    {
        print_error("No image built!");
        exit(1);
    }
    mlx_image_to_window(vars->mlx, vars->style->images->img, 100, 100);
    vars->style->images->img->instances[0].z = 1;
    d_wall = malloc(vars->pers->rays[0]->n_rays * sizeof(double));
    w_height = malloc(vars->pers->rays[0]->n_rays * sizeof(double));
    if (!d_wall || !w_height)
        mlx_terminate(vars->mlx);
    while (++i < vars->pers->rays[0]->n_rays)
    {
        d_wall[i] = distance2(vars->pers->x, vars->pers->y,
            vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
        printf("dist: %f | i = %d\n", d_wall[i], i);
        w_height[i] = d_wall[i] * 32 / 50;
        printf("w_h: %f\n", w_height[i]);
        wall_column(vars, i, w_height[i]);
    }
}
