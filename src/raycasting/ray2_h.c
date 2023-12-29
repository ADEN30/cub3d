
#include "../../include/cub3d.h"

void looking_up(t_vars *vars, double *r, double *ofs)
{
    double  atg;
    atg = atan(vars->pers->angle * M_PI / 180);

	r[1] = ((vars->pers->y / DIMENSION) * DIMENSION);
	if (vars->pers->angle == 270)
		r[0] = vars->pers->x;
	else
		r[0] = (vars->pers->y - r[1]) * atg + vars->pers->x;
	ofs[1] = -DIMENSION;
	if (vars->pers->angle == 270)
		ofs[0] = 0;
	else
		ofs[0] = -ofs[1] * atg;
}

void looking_down(t_vars *vars, double *r, double *ofs)
{
    double  atg;
    atg = atan(vars->pers->angle * M_PI / 180);

	r[1] = ((vars->pers->y / DIMENSION) * DIMENSION) + DIMENSION;
	if (vars->pers->angle == 90)
		r[0] = vars->pers->x;
	else
		r[0] = (vars->pers->y - r[1]) * atg + vars->pers->x;
	ofs[1] = DIMENSION;
	if (vars->pers->angle == 90)
		ofs[0] = 0;
	else
		ofs[0] = -ofs[1] * atg;
}

void never_h(t_vars *vars, double *r, int *i)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
	*i = max_xy(vars->map->X, vars->map->Y);
}

void horizontal_intersection(t_vars *vars, double *h)
{
    double  ray[2];
	double	ofs[2];
	int		i;
    
	i = 0;
	init_tabs(ray, ofs);
    if (vars->pers->angle == 0 || vars->pers->angle == 180)
		never_h(vars, ray, &i);
    else if (vars->pers->angle * M_PI / 180 < M_PI)
		looking_down(vars, ray, ofs);
    else if (vars->pers->angle * M_PI / 180 > M_PI)
		looking_up(vars, ray, ofs);
	while (i < max_xy(vars->map->X, vars->map->Y))
	{
		if (wall_vh(vars, ray, h))
			i = max_xy(vars->map->X, vars->map->Y);
		else
		{
			ray[0] += ofs[0];
			ray[1] += ofs[1];
			mlx_put_pixel(vars->pers->rays[0]->img, ray[0], ray[1], get_rgba(255, 0, 0, 255));
			i += 1;
		}
	}
}
