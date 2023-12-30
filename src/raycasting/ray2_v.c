
#include "../../include/cub3d.h"

void looking_left(t_vars *vars, double *r, double *ofs, char *face)
{
    double adjustedAngle;
    double atg;

	if (vars->pers->angle > 90)
		adjustedAngle = vars->pers->angle - 90;
	else
		adjustedAngle = 90 - vars->pers->angle;
    if (adjustedAngle != 0)
        atg = -tan(adjustedAngle * M_PI / 180);
    r[0] = ((vars->pers->x / DIMENSION) * DIMENSION) - 0.0001; 
    if (adjustedAngle == 0)
	{
        r[1] = vars->pers->y;
        ofs[1] = 0;
    }
	else
	{
        r[1] = (vars->pers->x - r[0]) * atg + vars->pers->y;
        ofs[1] = ofs[0] * atg;
    }
    ofs[0] = -DIMENSION;
	face[0] = 'W';
	printf("adjustedAngle = %f\n", adjustedAngle);
	printf("rv_l[0] = %f\n", r[0]);
	printf("rv_l[1] = %f\n", r[1]);
}

void looking_right(t_vars *vars, double *r, double *ofs, char *face)
{
	double atg;
    double adjustedAngle;
	
	if (vars->pers->angle > 270)
		adjustedAngle = vars->pers->angle - 270;
	else
		adjustedAngle = 90 - vars->pers->angle;
    if (adjustedAngle != 0)
        atg = tan(adjustedAngle * M_PI / 180);
    r[0] = ((int)(vars->pers->x / DIMENSION) + 1) * DIMENSION;
    if (adjustedAngle == 0)
	{
        r[1] = vars->pers->y;
        ofs[1] = 0;
    }
	else
	{
        ofs[1] = ofs[0] * atg;
        r[1] = (r[0] - vars->pers->x) * atg + vars->pers->y;
    }
    ofs[0] = DIMENSION;
	face[0] = 'E';
	printf("adjustedAngle = %f\n", adjustedAngle);
	printf("rv_r[0] = %f\n", r[0]);
	printf("rv_r[1] = %f\n", r[1]);
}

void never_v(t_vars *vars, double *r, int *i)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
	*i = max_xy(vars->map->X, vars->map->Y);
}
void vertical_intersection(t_vars *vars, double *v, char *face)
{
    double  ray[2];
	double	ofs[2];
	int		i;
    
	i = 0;
	init_tabs(ray, ofs);
    if (vars->pers->angle == 90 || vars->pers->angle == 270)
		never_v(vars, ray, &i);
	else if (vars->pers->angle > 90 && vars->pers->angle < 270)
		looking_left(vars, ray, ofs, face);
	else if ((vars->pers->angle > 0 && vars->pers->angle < 90)
		|| (vars->pers->angle > 270 && vars->pers->angle < 360))
		looking_right(vars, ray, ofs, face);
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
