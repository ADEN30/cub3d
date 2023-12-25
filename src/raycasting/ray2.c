#include "../../include/cub3d.h"

void vertical_intersection(t_vars *vars, double *x, double *y)
{
    double  tangent;
    double  x_step;
    double  y_step;
    bool    ray_right;

    tangent = tan(vars->pers->angle);
    if (vars->pers->angle > M_PI / 2 && vars->pers->angle < 3 * M_PI / 2)
        ray_right = false;
    else
        ray_right = true;
    if (ray_right)
        *x = *x + 1.0;
    *y = vars->pers->y + (*x - vars->pers->x) * tangent;
    if (ray_right)
        x_step = 1.0;
    else
        x_step = -1.0;
    y_step = x_step * tangent;
    *x += x_step;
    *y += y_step;
}

void horizontal_intersection(t_vars *vars, double *x, double *y)
{
    double  tangent;
    double  _step;
    double  y_step;
    bool    ray_up;
    
    tangent = tan(vars->pers->angle);
    if (vars->pers->angle > 0 && vars->pers->angle < M_PI)
        ray_up = true;
    else
        ray_up = false;
    if (ray_up == false)
        *y = *y + 1.0;
    *x = vars->pers->x + (*y - vars->pers->y) / tangent;
    if (ray_up)
        y_step = -1.0;
    else
        y_step = 1.0;
    x_step = y_step / tangent;
    *x += x_step;
    *y += y_step;
}

double dist(t_vars *vars, double x, double y)
{
    double dx;
    double dy;
    dx = x - (double)vars->pers->x;
    dy = y - (double)vars->pers->y;
    return sqrt(dx * dx + dy * dy);
}

void    check_lowest_move(t_vars *vars, double *x, double *y)
{
    double  h[2];
    double  v[2];
    double  dist_h;
    double  dist_v;

	h[0] = v[0] = *x;
    h[1] = v[1] = *y;
    horizontal_intersection(vars, &h[0], &h[1]);
    dist_h = dist(vars, h[0], h[1]);
    vertical_intersection(vars, &v[0], &v[1]);
    dist_v = dist(vars, v[0], v[1]);
        //printf("xv = %f yv = %f\n", v[0], v[1]);
        //printf("xh = %f yh = %f\n", h[0], h[1]);
    if (dist_h < dist_v)
    {
        *x = h[0];
        *y = h[1];
    }
    else
    {
        *x = v[0];
        *y = v[1];
    }
}

int test_wall2(t_vars* vars, double x, double y)
{
	if (vars->map->tab[(int)y / DIMENSION][(int)x / DIMENSION] == 1)
        return (1);
    return 0;
}

void	start_plan(t_vars* vars)
{
	double		x;
	double		y;
	double 		angles;
	int			i;

	angles = vars->pers->angle;
	i = 599;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	vars->pers->rays[0]->points = malloc(sizeof(t_point) * 600);
    //printf("Angle actuel: %f\n", vars->pers->angle);
	while (vars->pers->angle - (FOV / 2) < angles + (FOV / 2))
	{
        y = vars->pers->y;
        x = vars->pers->x;
        int count = 0;
		while (!test_wall2(vars, x, y) && x > 0 && x < vars->mlx->width && y > 0 && y < vars->mlx->height)
		{ 
			mlx_put_pixel(vars->pers->rays[0]->img, round(x), round(y), get_rgba(255, 0, 0, 255));
            check_lowest_move(vars, &x, &y);
            printf("x = %f | y = %f\n", x, y);
            printf("count = %d\n", count++);
            sleep(1);
		}
		vars->pers->rays[0]->points[i].y = y;
		vars->pers->rays[0]->points[i].x = x;
		i--;
		vars->pers->angle += 0.1 ;
	}
    vars->pers->angle = angles - (FOV / 2);
}
