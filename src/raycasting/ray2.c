#include "../../include/cub3d.h"

char    check_move(t_vars *vars, double *x, double *y)
{
    double  h[2];
    double  dist_h;
    double  v[2];
    double  dist_v;
    char    face[2];

	h[0] = v[0] = *x;
	h[1] = v[1] = *y;
    face[0] = face[1] = 'C';
    horizontal_intersection(vars, h, face);
    dist_h = dist(vars, h[0], h[1]);
    //printf("h[0] = %f\n", h[0]);
    //printf("h[1] = %f\n", h[1]);
    printf("dist_h = %f\n", dist_h);
    printf("\n");
    vertical_intersection(vars, v, face);
    dist_v = dist(vars, v[0], v[1]);
    //printf("v[0] = %f\n", v[0]);
    //printf("v[1] = %f\n", v[1]);
    printf("dist_v = %f\n", dist_v);
    if (dist_h <= dist_v || dist_v == 0)
    {
        if (face[1] == 'N')
            *y = h[1];
        else
            *y = h[1];
        *x = h[0];
        printf("face[1] = %c\n", face[1]);
        return (face[1]);
    }
    else if (dist_v < dist_h || dist_h == 0)
    {
        if (face[0] == 'W')
            *x = v[0] + 0.0001;
        else
            *x = v[0];
        *y = v[1];
        printf("face[0] = %c\n", face[0]);
        return (face[0]);
    }
    return ('C');
}

int normalizeAngle(int angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}

void	start_plan(t_vars* vars)
{
	double		x;
	double		y;
	int			i;

	i = 9;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	vars->pers->rays[0]->points = malloc(sizeof(t_point) * 10);
	vars->map->face = ft_calloc(sizeof(char), (10 + 1));
    if (!vars->pers->rays[0]->points || !vars->map->face)
        EXIT_FAILURE;
    //printf("\n");
    //printf("angle = %f\n", vars->pers->angle);
    vars->pers->angle = vars->pers->angle + 30;
    //printf("angle = %f\n", vars->pers->angle);
    printf("vars->pers->x = %d\n", vars->pers->x);
    printf("vars->pers->y = %d\n", vars->pers->y);
    //printf("\n");
    mlx_put_pixel(vars->pers->rays[0]->img, vars->pers->x, vars->pers->y, get_rgba(255, 0, 0, 255));
	while (i >= 0)
	{
        printf("\n");
        vars->pers->angle = normalizeAngle(vars->pers->angle);
        printf("angle = %f\n", vars->pers->angle);
        y = vars->pers->y;
        x = vars->pers->x;
        vars->map->face[i] = check_move(vars, &x, &y);
        printf("x = %d\n", (int)x);
        printf("y = %d\n", (int)y);
        mlx_put_pixel(vars->pers->rays[0]->img, (int)x, (int)y, get_rgba(255, 0, 0, 255));
        vars->pers->rays[0]->points[i].y = y;
        vars->pers->rays[0]->points[i].x = x;
        i--;
        vars->pers->angle -= 1;
        printf("\n");
	}
    vars->pers->angle = vars->pers->angle + 30;
}
