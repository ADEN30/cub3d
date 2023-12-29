#include "../../include/cub3d.h"

void    check_move(t_vars *vars, double *x, double *y)
{
    //double  h[2];
    //double  dist_h;
    double  v[2];
    //double  dist_v;

	//h[0] = v[0] = *x;
	//h[1] = v[1] = *y;
    //horizontal_intersection(vars, h);
    //dist_h = dist(vars, h[0], h[1]);
    v[1] = *y;
    v[0] = *x;
    vertical_intersection(vars, v);
    //dist_v = dist(vars, v[0], v[1]);
    //if (dist_h <= dist_v)
    //{
        //*x = h[0];
        //*y = h[1];
    //}
    //else
    //{
        *x = v[0];
        *y = v[1];
    //}
    printf("x = %f | y = %f\n", *x, *y);
}

void    print_ray(t_vars *vars, double x, double y)
{
    mlx_put_pixel(vars->pers->rays[0]->img, x, y, get_rgba(255, 0, 0, 255));
}

void	start_plan(t_vars* vars)
{
	double		x;
	double		y;
	//double 		angles;
	//int			i;

	//angles = vars->pers->angle;
	//i = 5;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	//vars->pers->rays[0]->points = malloc(sizeof(t_point) * 6);
    //printf("angle + FOV/2 = %f\n", angles + (FOV / 2));
    mlx_put_pixel(vars->pers->rays[0]->img, round(vars->pers->x), round(vars->pers->y), get_rgba(255, 0, 0, 255));
	//while (vars->pers->angle  < angles + (FOV / 2))
	//{
        printf("angle = %f\n", vars->pers->angle);
        y = vars->pers->y;
        x = vars->pers->x;
        check_move(vars, &x, &y);
        print_ray(vars, x, y);
        //vars->pers->rays[0]->points[i].y = y;
        //vars->pers->rays[0]->points[i].x = x;
        //i--;
       //vars->pers->angle += 10;
	//}
    //vars->pers->angle = angles - (FOV / 2);
}
