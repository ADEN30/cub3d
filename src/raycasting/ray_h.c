
#include "../../include/cub3d.h"

void looking_up(t_vars *vars, double *r, double *ofs , char *face)
{
	double tg;

	tg = 1 / tan(vars->pers->angle);
	r[1] = (((int)vars->pers->y / DIMENSION) * DIMENSION) - 0.0001;
	ofs[1] = -DIMENSION;
	if (vars->pers->angle == M_PI / 2)
	{
		r[0] = vars->pers->x;
		ofs[0] = 0;
	}
	else
	{
		r[0] = (vars->pers->y - r[1]) * tg + vars->pers->x;
		ofs[0] = -ofs[1] * tg;
	}
    face[1] = 'N';
}

void looking_down(t_vars *vars, double *r, double *ofs, char *face)
{
	double tg;

	tg = 1 / tan(vars->pers->angle);
	r[1] = (((int)vars->pers->y / DIMENSION) * DIMENSION) + DIMENSION;
	ofs[1] = DIMENSION;
	if (vars->pers->angle == 3 * M_PI / 2)
	{
		r[0] = vars->pers->x;
		ofs[0] = 0;
	}
	else
	{
		r[0] = (vars->pers->y - r[1]) * tg + vars->pers->x;
		ofs[0] = -ofs[1] * tg;
	}
    face[1] = 'S';
}

void horizontal_intersection(t_vars *vars, double *h, char *face)
{
    double  ray[2];
	double	ofs[2];
    
	init_tabs(ray, ofs);
    if (vars->pers->angle == 0 || vars->pers->angle == M_PI)
	{
		never_vh(vars, ray);
		return ;
	}
    else if (vars->pers->angle < M_PI)
		looking_up(vars, ray, ofs, face);
    else if (vars->pers->angle > M_PI)
		looking_down(vars, ray, ofs, face);
	find_wall_vh(vars, h, ray, ofs);
}
