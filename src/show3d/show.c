#include "../../include/cub3d.h"

static int  next_int(int a, int b)
{
    double  rslt;
    int     next_int;

    rslt = (double) a / b;
    if (rslt >= 0)
        next_int = (int)(rslt + 0.5);
    else
        next_int = (int)(rslt - 0.5);
    return next_int;
}

static char which_wall(t_vars *vars, double x, double y, int ang)
{
    if (vars->pers->rays[0]->points->x >= x)
    {
        if (vars->pers->rays[0]->points->y >= y)
        {
            if (ang >= 45)
                return ('S');
            else
                return ('E');
        } 
        if (vars->pers->rays[0]->points->y < y)
        {
            if (ang >= 270 && ang <= 315)
                return ('N');
            else
                return ('E');
        } 
    }
    else
    {
        if (vars->pers->rays[0]->points->y >= y)
        {
            if (ang <= 135)
                return ('S');
            else
                return ('W');
        } 
        if (vars->pers->rays[0]->points->y < y)
        {
            if (ang >= 225)
                return ('N');
            else
                return ('W');
        } 
    }
    return (0);
}

static void wall_column(t_vars *vars, int i, double w_height, int ang)
{
    int     j;
    char    c;

    j = -1;
    while (++j < vars->mlx->height)
    {
        if (j > (vars->mlx->height / 2 - (w_height / 2))
            && j < (vars->mlx->height / 2 + (w_height / 2)))
        {
            c = which_wall(vars, i, j, ang);
            printf("c= %c\n", c);
            if (c == 'E')
                mlx_put_pixel(vars->style->images->img, i, j, 50);
            else if (c == 'N')
                mlx_put_pixel(vars->style->images->img, i, j, 100);
            else if (c == 'S')
                mlx_put_pixel(vars->style->images->img, i, j, 150);
            else if (c == 'W')
                mlx_put_pixel(vars->style->images->img, i, j, 200);
            //mlx_put_pixel(vars->style->images->img, i, j, pixel_color(vars, i, j, w_height));
            else
                exit(0);
        }
    }
}

void    show_vue(void *param)
{
    t_vars  *vars;
    double  *d_wall;
    double  *w_height;
    int     i;
    int     j;
    int     count;
    int    k; 
    double ang;
    int l;

    vars = param;
    ang = vars->pers->orientation;
    count = next_int(vars->mlx->width, vars->pers->rays[0]->n_rays);
    //double ang = (ang - 60 / 2) * M_PI / 180;
    //printf("angle = %f ang = %f\n", vars->pers->rays[0]->angle, ang);
    i = 0;
    j = 0;
    w_height = NULL;
    if (vars->style->images->img)
        mlx_delete_image(vars->mlx, vars->style->images->img);
    vars->style->images->img = mlx_new_image(vars->mlx, vars->mlx->width,
        vars->mlx->height);
    //if (!vars->style->images->img)
    //{
        //print_error("No image built!");
        //exit(1);
    //}
    l = 0;
    d_wall = malloc(vars->pers->rays[0]->n_rays * sizeof(double));
    w_height = malloc(vars->pers->rays[0]->n_rays * sizeof(double));
    if (!d_wall || !w_height)
        mlx_terminate(vars->mlx);
    while (j < vars->mlx->width)
    {
        d_wall[i] = distance(vars->pers->x, vars->pers->y,
            vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
        w_height[i] = 32 / (d_wall[i] * 0.004);
        //printf("%f\n", w_height[i]);
        //w_height[i] = w_height[i] / (cos((vars->pers->rays[0]->angle * M_PI / 180) - ang));
        //printf("%f\n", w_height[i]);
        //sleep(1);
        k = 0;
        while (k < count)
        {
            if (l < 25)
                l++; 
            if (l == 25)
            {
                l = 0;
                ang += 1;
            }
            printf("ang = %f | l= %d\n", ang, l);
            wall_column(vars, j++, w_height[i], ang);
            k++;
        }
        //ang = (60 / vars->mlx->height) * M_PI / 180;
        i++;
    }
    mlx_image_to_window(vars->mlx, vars->style->images->img, 0, 0);
    vars->style->images->img->instances[0].z = 1;
}
