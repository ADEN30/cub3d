
#include "../../include/cub3d.h"

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

int wall_vh(t_vars* vars, double *r, double *xy)
{
	int mX;
	int mY;

	mX = (int)r[0] / DIMENSION;
	mY = (int)r[1] / DIMENSION;
	if (mX > 0 && mX < vars->map->X && mY > 0 && mY < vars->map->Y && vars->map->tab[mY][mX] == 49)
	{
		xy[0] = r[0];
		xy[1] = r[1];
		return (1);
	}
    return 0;
}

int max_xy(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}