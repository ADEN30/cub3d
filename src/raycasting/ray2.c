#include "../../include/cub3d.h"

char    change_xy(double *x, double *y, double *xy, char face)
{
    *y = xy[1];
    *x = xy[0];
    return (face);
}

char    check_move(t_vars *vars, double *x, double *y)
{
    double  h[2];
    double  dst[2];
    double  v[2];
    char    face[2];
    double  ra;

	h[0] = v[0] = *x;
	h[1] = v[1] = *y;
    face[0] = face[1] = '0';
    ra = vars->pers->angle;
    vars->pers->angle = vars->pers->angle + (1 * M_PI / 180) * 30;
    if (vars->pers->angle < 0)
        vars->pers->angle =  2 * M_PI + vars->pers->angle;
    horizontal_intersection(vars, h, face);
    dst[0] = dist(vars, h[0], h[1]);
    vertical_intersection(vars, v, face);
    dst[1] = dist(vars, v[0], v[1]);
    vars->pers->angle = ra;
    if ((dst[0] <= dst[1] && dst[0] != 0) || dst[1] == 0)
        return (change_xy(x, y, h, face[1]));
    else if ((dst[1] < dst[0] && dst[1] != 0) || dst[0] == 0)
        return (change_xy(x, y, v, face[0]));
    return ('0');
}

void	start_plan(t_vars* vars)
{
	double		x;
	double		y;
	int			i;

	i = 599;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	vars->pers->rays[0]->points = malloc(sizeof(t_point) * 600);
	vars->map->face = ft_calloc(sizeof(char), (600 + 1));
    if (!vars->pers->rays[0]->points || !vars->map->face)
        EXIT_FAILURE;
    mlx_put_pixel(vars->pers->rays[0]->img, vars->pers->x, vars->pers->y, get_rgba(255, 0, 0, 255));
	while (i >= 0)
	{
        y = vars->pers->y;
        x = vars->pers->x;
        vars->map->face[i] = check_move(vars, &x, &y);
        mlx_put_pixel(vars->pers->rays[0]->img, (int)x, (int)y, get_rgba(255, 0, 0, 255));
        vars->pers->rays[0]->points[i].y = y;
        vars->pers->rays[0]->points[i].x = x;
        i--;
        vars->pers->angle -= 0.1 * M_PI / 180;
	}
    vars->pers->angle = vars->pers->angle + (30 * M_PI / 180);
}
