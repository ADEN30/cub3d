
#include "../../include/cub3d.h"

void looking_up(t_vars *vars, double *r, double *ofs , char *face)
{
    double adjustedAngle;
	double atg;

	if (vars->pers->angle > 90)
		adjustedAngle = vars->pers->angle - 90;
	else
		adjustedAngle = 90 - vars->pers->angle;
    if (adjustedAngle == 0)
	{
        r[0] = vars->pers->x;
        ofs[0] = 0;
    }
	else
	{
        atg = -tan(adjustedAngle * M_PI / 180);
        r[0] = (vars->pers->y - ((int)(vars->pers->y / DIMENSION) * DIMENSION))
			* atg + vars->pers->x;
        ofs[0] = DIMENSION * atg;
    }
    r[1] = ((int)(vars->pers->y / DIMENSION) * DIMENSION) - 0.0001;
    ofs[1] = -DIMENSION;
    face[1] = 'N';
	printf("adjustedAngle = %f\n", adjustedAngle);
	printf("rh_u[0] = %f\n", r[0]);
	printf("rh_u[1] = %f\n", r[1]);
}

void looking_down(t_vars *vars, double *r, double *ofs, char *face)
{
    double adjustedAngle;
	double atg;
	
	if (vars->pers->angle > 270)
		adjustedAngle = vars->pers->angle - 270;
	else	
		adjustedAngle = 270 - vars->pers->angle;
    if (adjustedAngle == 0)
	{
        r[0] = vars->pers->x;
        ofs[0] = 0;
    }
	else
	{
        atg = tan(adjustedAngle * M_PI / 180);
        r[0] = ((DIMENSION - (vars->pers->y % DIMENSION)) * atg) + vars->pers->x;
        ofs[0] = DIMENSION * atg;
    }
    r[1] = ((int)(vars->pers->y / DIMENSION) + 1) * DIMENSION;
    ofs[1] = DIMENSION;
	face[1] = 'S';
	printf("adjustedAngle = %f\n", adjustedAngle);
	printf("rh_d[0] = %f\n", r[0]);
	printf("rh_d[1] = %f\n", r[1]);
}

void never_h(t_vars *vars, double *r, int *i)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
	*i = max_xy(vars->map->X, vars->map->Y);
}

void horizontal_intersection(t_vars *vars, double *h, char *face)
{
    double  ray[2];
	double	ofs[2];
	int		i;
    
	i = 0;
	init_tabs(ray, ofs);
    if (vars->pers->angle == 0 || vars->pers->angle == 180)
		never_h(vars, ray, &i);
    else if (vars->pers->angle > 180 && vars->pers->angle < 360)
		looking_down(vars, ray, ofs, face);
    else if (vars->pers->angle > 0 && vars->pers->angle < 180)
		looking_up(vars, ray, ofs, face);
	while (i < max_xy(vars->map->X, vars->map->Y))
	{
		if (wall_vh(vars, ray, h))
			i = max_xy(vars->map->X, vars->map->Y);
		else
		{
			ray[0] += ofs[0];
			ray[1] += ofs[1];
			i += 1;
		}
	}
}
