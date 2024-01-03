#include "../../include/cub3d.h"

void	fill_tab(t_vars *vars, char **line)
{
	int		i;
	int		j;

	j = 0;
	while (j < vars->map->Y)
	{
		i = 0;
		while (i < vars->map->X)
		{
			vars->map->tab[j][i] = (int)line[0][i];
			i++;
		}
		free(*line);
		*line = get_next_line(vars->map->fd);
		j++;
	}
}

int **tab_alloc(int x, int y)
{
	int	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(y, sizeof(int *));
	if (tab == NULL)
		return (NULL);
	while (i < y)
	{
		tab[i] = ft_calloc(x, sizeof(int));
		if (tab[i] == NULL)
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

char *starting_map(t_vars *vars)
{
	int		j;
	char	*line;

	line = get_next_line(vars->map->fd);
	while (*line)
	{
		j = 0;
		while (line[j] == ' ' || line[j] == '1')
			j++;
		if (line[j] == '\n' && j > 0)
			break ;
		else
		{
			free(line);
			line = get_next_line(vars->map->fd);
		}
	}
	return (line);
}

void define_xy(t_vars *vars, char **tmp, int *x, int *y)
{
	int	xi;

	xi = 0;
	*x = ft_strlen(*tmp);
	while (*tmp && !line_isprint(*tmp))
	{
		xi = ft_strlen(*tmp);
		if (xi > *x)
			*x = xi;
		free(*tmp);
		*tmp = get_next_line(vars->map->fd);
		(*y)++;
	}
	if (*tmp)
		free(*tmp);
	*x -= 1;
	close(vars->map->fd);
}

int	create_tab(t_vars *vars, char **line, char *argv)
{
	int		x;
	int		y;

	x = y = 0;
	while (line_isprint(*line))
	{
		free(*line);
		*line = get_next_line(vars->map->fd);
	}
	define_xy(vars, line, &x, &y);
	vars->map->fd = open(argv, O_RDONLY);
	*line = starting_map(vars);
	vars->map->tab = tab_alloc(x, y);
	if (!vars->map->tab)
		return (1);
	vars->map->X = x;
	vars->map->Y = y;
	fill_tab(vars, line);
	return (0);
}
