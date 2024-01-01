
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

void never_vh(t_vars *vars, double *r)
{
	r[1] = vars->pers->y;
	r[0] = vars->pers->x;
}

int wall_vh(t_vars* vars, double *r, double *xy, int *mp)
{
	if (mp[0] >= 0 && mp[0] <= vars->map->X && mp[1] >= 0 && mp[1] <= vars->map->Y
		&& vars->map->tab[mp[1]][mp[0]] == 49)
	{
		xy[0] = r[0];
		xy[1] = r[1];
		return (1);
	}
    return 0;
}

void	find_wall_vh(t_vars *vars, double *xy, double *ray, double *ofs)
{
	int i;
	int	mp[2];

	i = 0;
	while (i < max_xy(vars->map->X, vars->map->Y))
	{
		mp[0] = (int)ray[0] / DIMENSION;
		mp[1] = (int)ray[1] / DIMENSION;
		if (mp[0] >= vars->map->X || mp[1] >= vars->map->Y || mp[0] < 0 || mp[1] < 0)
		{
			xy[0] = vars->pers->x;
			xy[1] = vars->pers->y;
			return ;
		}
		if (wall_vh(vars, ray, xy, mp))
			return ;
		else
		{
			ray[0] += ofs[0];
			ray[1] += ofs[1];
			i += 1;
		}
	}
}
