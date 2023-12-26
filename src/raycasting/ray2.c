#include "../../include/cub3d.h"

void vertical_intersection(t_vars *vars, double *x, double *y)
{
    double  tangent;
    bool    ray_right;

    tangent = tan(vars->pers->angle * M_PI / 180);
    if (vars->pers->angle * M_PI / 180 > M_PI / 2 && (vars->pers->angle * M_PI / 180) < 3 * M_PI / 2)
        ray_right = false;
    else
        ray_right = true;
    //DIMENSION a changer
    if (ray_right)
        *x = floor(*x / DIMENSION) * DIMENSION + DIMENSION;
    else
        *x = floor(*x / DIMENSION) * DIMENSION - 1;
    *y = vars->pers->y + (*x - vars->pers->x) * tangent;
}

void horizontal_intersection(t_vars *vars, double *x, double *y)
{
    double  tangent;
    bool    ray_up;
    

    tangent = tan(vars->pers->angle * M_PI / 180);
    if (vars->pers->angle * M_PI / 180 > 0 && (vars->pers->angle * M_PI / 180) < M_PI)
        ray_up = true;
    else
        ray_up = false;
    if (ray_up)
        *y = floor(*y / DIMENSION) * DIMENSION - 1;
    else
        *y = floor(*y / DIMENSION) * DIMENSION + DIMENSION;
    if (tangent != 0)
        *x = vars->pers->x + (*y - vars->pers->y) / tangent;
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
    // Revoir le calcul du pas pour le prochain pixel : touver un truc coherent
    horizontal_intersection(vars, &h[0], &h[1]);
    dist_h = dist(vars, h[0], h[1]);
    vertical_intersection(vars, &v[0], &v[1]);
    dist_v = dist(vars, v[0], v[1]);
    printf("xv= %f yv= %f\n", v[0], v[1]);
    printf("xh= %f yh= %f\n", h[0], h[1]);
    //probleme de choix en fonction de l'angle
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
	while (vars->pers->angle < angles + (FOV / 2))
	{
        //printf("Angle actuel: %f\n", vars->pers->angle);
        y = vars->pers->y;
        x = vars->pers->x;
		while (!test_wall2(vars, x, y) && x > 0 && x < vars->mlx->width && y > 0 && y < vars->mlx->height)
		{ 
			mlx_put_pixel(vars->pers->rays[0]->img, round(x), round(y), get_rgba(255, 0, 0, 255));
            check_lowest_move(vars, &x, &y);
            printf("x = %f | y = %f\n", x, y);
		}
		vars->pers->rays[0]->points[i].y = y;
		vars->pers->rays[0]->points[i].x = x;
		i--;
		vars->pers->angle += 0.1 ;
	}
    vars->pers->angle = angles - (FOV / 2);
}
