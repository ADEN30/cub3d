#include "../../include/cub3d.h"

static int	case_accept(t_list *list, int x, int y)
{
	char	c;

	c = find_case(list, x, y);
	if (!ft_strchr("01NSEW ", c))
		return (print_error("Error : The map can not contain anything other than '01NSEW' characters"));
	if (ft_strchr("0NSEW", c))
	{
		if (!ft_strchr("01NSEW", find_case(list, x - 1, y))
			|| (x == 0 && ft_strchr("0NSEW", c)))
			return (print_error("Error : The map is not closed"));
		if (!ft_strchr("01NSEW", find_case(list, x + 1, y))
			|| (!find_case(list, x + 1, y) && ft_strchr("0NSEW", c)))
			return (print_error("Error : The map is not closed"));
		if ((!ft_strchr("01NSEW", find_case(list, x, y - 1)))
			|| (y == 0 && ft_strchr("0NSEW", c)))
			return (print_error("Error : The map is not closed"));
		if ((!ft_strchr("01NSEW", find_case(list, x, y + 1)))
			|| (!find_case(list, 0, y + 1) && ft_strchr("0NSEW", c)))
			return (print_error("Error : The map is not closed"));
	}
	return (0);
}

int	test_map(t_vars *vars)
{
	t_list	*list;
	int		x;
	int		y;
	int		start_point;

	y = 0;
	start_point = 0;
	list = vars->map->lines;
	while (find_case(list, 0, y))
	{
		x = 0;
		while (find_case(list, x, y))
		{
			if (ft_strchr("NSEW", find_case(list, x, y)))
				start_point++;
			if (case_accept(list, x, y))
				return (1);
			x++;
		}
		y++;
	}
	if (start_point != 1)
		return (print_error("Error : The map contains more than one character position"));
	return (0);
}
