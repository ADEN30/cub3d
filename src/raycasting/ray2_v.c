
#include "../../include/cub3d.h"

void looking_left(t_vars *vars, double *r, double *ofs)
{
    double  tg;
	tg = -tan(vars->pers->angle * M_PI / 180);

	r[0] = ((vars->pers->x / DIMENSION) * DIMENSION);
	if (vars->pers->angle == 180)
		r[1] = vars->pers->y;
	else
		r[1] = (vars->pers->x - r[0]) * tg + vars->pers->y;
	ofs[0] = -DIMENSION;
	if (vars->pers->angle == 18070)
		ofs[1] = 0;
	else
		ofs[1] = -ofs[0] * tg;
}

void looking_right(t_vars *vars, double *r, double *ofs)
{
    double  tg;
    tg = -tan(vars->pers->angle * M_PI / 180);

	r[0] = ((vars->pers->x / DIMENSION) * DIMENSION) + DIMENSION;
	if (vars->pers->angle == 0)
		r[1] = vars->pers->y;
	else
		r[1] = (vars->pers->x - r[0]) * tg + vars->pers->y;
	ofs[0] = DIMENSION;
	if (vars->pers->angle == 0)
		ofs[1] = 0;
	else
		ofs[1] = -ofs[0] * tg;
}

void never_v(t_vars *vars, double *r, int *i)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
	*i = max_xy(vars->map->X, vars->map->Y);
}
void vertical_intersection(t_vars *vars, double *v)
{
    double  ray[2];
	double	ofs[2];
	int		i;
    
	i = 0;
	init_tabs(ray, ofs);
    if (vars->pers->angle == 90 || vars->pers->angle == 270)
		never_v(vars, ray, &i);
    else if ((vars->pers->angle * M_PI / 180 > M_PI /2
		&& vars->pers-> angle * M_PI / 180 < 3 * M_PI / 2))
		looking_left(vars, ray, ofs);
    else if ((vars->pers->angle * M_PI / 180 < M_PI /2
		|| vars->pers-> angle * M_PI / 180 > 3 * M_PI / 2))
		looking_right(vars, ray, ofs);
	while (i < max_xy(vars->map->X, vars->map->Y))
	{
		if (wall_vh(vars, ray, v))
			i = max_xy(vars->map->X, vars->map->Y);
		else
		{
			ray[0] += ofs[0];
			ray[1] += ofs[1];
			i += 1;
		}
	}
}
