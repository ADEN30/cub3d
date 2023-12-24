#include "../../include/cub3d.h"

void vertical_intersection(t_vars *vars, double *x, double *y)
{
    double tangent;
    double x_step;
    double y_step;
    bool ray_right;

    tangent = tan(vars->pers->angle);
    ray_right = (vars->pers->angle > M_PI / 2 && vars->pers->angle < 3 * M_PI / 2) ? false : true;
    *x = ray_right ? (double)(vars->pers->x) + 1.0 : (double)(vars->pers->x);
    *y = vars->pers->y + (*x - vars->pers->x) * tangent;
    x_step = ray_right ? 1.0 : -1.0;
    y_step = x_step * tangent;
    *x += x_step;
    *y += y_step;
}

void horizontal_intersection(t_vars *vars, double *x, double *y)
{
    double tangent;
    double x_step;
    double y_step;
    bool ray_up;
    
    tangent = tan(vars->pers->angle);
    ray_up = (vars->pers->angle > 0 && vars->pers->angle < M_PI) ? true : false;
    *y = ray_up ? (double)(vars->pers->y) : (double)(vars->pers->y) + 1.0;
    *x = vars->pers->x + (*y - vars->pers->y) / tangent;
    y_step = ray_up ? -1.0 : 1.0;
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

    h[0] = h[1] = v[0] = v[1] = 0;
    horizontal_intersection(vars, &h[0], &h[1]);
    dist_h = dist(vars, h[0], h[1]);
    vertical_intersection(vars, &v[0], &v[1]);
    dist_v = dist(vars, v[0], v[1]);
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
    mlx_image_t *wall;
    size_t      i;

    i = 0;
    wall = vars->style->images->wall_image;
    // Vérifier si les coordonnées de la grille sont à l'intérieur de la carte
    //if (mapX < 0 || mapX >= varsMAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
        //return 0;  // En dehors de la carte
	while (i < wall->count)
    {
        if (x == wall->instances[i].x && y == wall->instances[i].y)
            return (1);
        i++;
    }
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
    printf("Angle actuel: %f\n", vars->pers->angle);
	while (vars->pers->angle < angles + (FOV / 2))
	{
        y = vars->pers->y;
        x = vars->pers->x;
		while (!test_wall2(vars, x, y) && x > 0 && x < vars->mlx->width && y > 0 && y < vars->mlx->height)
		{ 
			mlx_put_pixel(vars->pers->rays[0]->img, round(x), round(y), get_rgba(255, 0, 0, 255));
            check_lowest_move(vars, &x, &y);
            //ne sort pas de cette boucle ! a travailler!
		}
        printf("x = %f | y = %f \n", x, y);
		vars->pers->rays[0]->points[i].y = y;
		vars->pers->rays[0]->points[i].x = x;
		i--;
		vars->pers->angle += 0.1 ;
        printf("Angle actuel: %f\n", vars->pers->angle);
        sleep(10);
	}
    vars->pers->angle = angles - (FOV / 2);
}
