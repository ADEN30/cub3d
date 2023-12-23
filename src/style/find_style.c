#include "../../include/cub3d.h"

static int	check_config(t_vars *vars)
{
	if (!vars->style->north_path
		|| !vars->style->south_path
		|| !vars->style->west_path
		|| !vars->style->east_path
		|| !vars->style->define_floor
		|| !vars->style->define_roof)
		return (1);
	return (0);
}

int start_map(char *line)
{
	int i;
	int j;

	i = j = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '1')
		{
			i++;
			j++;
		}
		else
			return (0);
	}
	if (j != 0)
		return (1);
	return (0);
}

static int check_style(int *check)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (check[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void init_check(int *check)
{
	check[0] = 0;
	check[1] = 0;
	check[2] = 0;
	check[3] = 0;
	check[4] = 0;
	check[5] = 0;
}

int	find_all_style(t_vars *vars, char **line)
{
	int	check[6];
	init_check(check);
	while (check_config(vars))
	{
		if (*line)
		{
			if ((start_map(*line) && !check_style(check))
				|| find_style(*line, vars, check))
			{
				free(*line);
				return (1);
			}
			free(*line);
			*line = get_next_line(vars->map->fd);
		}
		else
			break;
	}
	return (0);
}
