
#include "../../include/cub3d.h"

int max_xy(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

double dist(t_vars *vars, double x, double y)
{
    double dx;
    double dy;
    dx = x - (double)vars->pers->x;
    dy = y - (double)vars->pers->y;
    return sqrt(dx * dx + dy * dy);
}

void init_tabs(double *r, double *ofs)
{
	r[0] = 0;
	r[1] = 0;
	ofs[0] = 0;
	ofs[1] = 0;
}
