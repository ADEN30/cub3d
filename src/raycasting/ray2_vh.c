
#include "../../include/cub3d.h"

int	isnegative(double angle)
{
	if (angle < 0)
	{
		printf("///NEGATIVE///\n");
		return (1);
	}
	return (0);
}

void never_v(t_vars *vars, double *r, int *i)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
	*i = max_xy(vars->map->X, vars->map->Y);
}

void never_h(t_vars *vars, double *r, int *i)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
	*i = max_xy(vars->map->X, vars->map->Y);
}

int wall_vh(t_vars* vars, double *r, double *xy)
{
	int mX;
	int mY;
	
	mX = (int)r[0] / DIMENSION;
	mY = (int)r[1] / DIMENSION;
	if (mX > vars->map->X || mY > vars->map->Y || mX < 0 || mY < 0)
	{
		xy[0] = vars->pers->x;
		xy[1] = vars->pers->y;
		printf("///OUT OF BOUNDERIES///\n");
		return (2);
	}
	else if (mX >= 0 && mX <= vars->map->X && mY >= 0 && mY <= vars->map->Y
		&& vars->map->tab[mY][mX] == 49)
	{
		xy[0] = r[0];
		xy[1] = r[1];
		return (1);
	}
    return 0;
}
