#include "../../include/cub3d.h"

static int	case_accept(t_vars *vars, int x, int y, char c)
{
	if (!ft_strchr("01NSEW ", c))
		return (print_error("Error : The map can not contain anything other than '01NSEW ' characters"));
	if (ft_strchr("0NSEW", c))
	{
		if (!ft_strchr("01NSEW ", (char)vars->map->tab[y][x - 1])
			|| (x == 0 && ft_strchr("0NSEW", c)))
			return (print_error("Error : The map is not closed"));
		if (!ft_strchr("01NSEW ", (char)vars->map->tab[y][x + 1])
			|| (!(char)vars->map->tab[y][x + 1] && ft_strchr("0NSEW ", c)))
			return (print_error("Error : The map is not closed"));
		if ((!ft_strchr("01NSEW ", (char)vars->map->tab[y - 1][x]))
			|| (y == 0 && ft_strchr("0NSEW ", c)))
			return (print_error("Error : The map is not closed"));
		if ((!ft_strchr("01NSEW ", (char)vars->map->tab[y + 1][x]))
			|| (!(char)vars->map->tab[y + 1][x] && ft_strchr("0NSEW ", c)))
			return (print_error("Error : The map is not closed"));
	}
	return (0);
}

int	check_map(t_vars *vars)
{
	int		x;
	int		y;
	int		start_point;

	y = -1;
	start_point = 0;
	while (++y < vars->map->Y)
	{
		x = -1;
		while (++x < vars->map->X)
		{
			if (ft_strchr("NSEW ", (char)vars->map->tab[y][x]))
				start_point++;
			if (case_accept(vars, x, y, (char)vars->map->tab[y][x]))
				return (1);
		}
	}
	if (start_point != 1)
		return (print_error("Error : The map contains no or more than one character position"));
	return (0);
}
