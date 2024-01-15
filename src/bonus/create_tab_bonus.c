/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:15:49 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/15 15:59:45 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	fill_tab(t_vars *vars, char **line)
{
	int		x;
	int		y;

	y = 0;
	while (line[0] && y < vars->map->y)
	{
		x = 0;
		while (x < vars->map->x)
		{
			if (!line[0][x] || line[0][x] == '\n')
			{
				while (x < vars->map->x)
				{
					vars->map->tab[y][x] = 32;
					x++;
				}
				break ;
			}
			vars->map->tab[y][x] = (int)line[0][x];
			x++;
		}
		free(*line);
		*line = get_next_line(vars->map->fd);
		y++;
	}
}

static int	**copy_map(t_vars *vars)
{
	int		x;
	int		y;
	int		**map;

	y = -1;
	map = malloc(vars->map->y * sizeof(int *));
	if (!map)
		return (NULL);
	while (++y < vars->map->y)
	{
		x = -1;
		map[y] = malloc(vars->map->x * sizeof(int));
		if (!map[y])
		{
			while (y > 0)
				free(map[--y]);
			free(map);
			return (NULL);
		}
		while (++x < vars->map->x)
			map[y][x] = vars->map->tab[y][x];
	}
	return (map);
}

static int	**tab_alloc(t_vars *vars)
{
	int	**tab;
	int	i;

	i = 0;
	tab = malloc(vars->map->y * sizeof(int *));
	if (!tab)
		return (NULL);
	while (i < vars->map->y)
	{
		tab[i] = malloc(vars->map->x * sizeof(int));
		if (!tab[i])
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

static char	*starting_map(t_vars *vars)
{
	int		j;
	char	*line;

	line = get_next_line(vars->map->fd);
	while (line)
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

int	create_tab(t_vars *vars, char *argv)
{
	char	*line;

	vars->map->fd = open(argv, O_RDONLY);
	if (vars->map->fd == -1)
		return (1);
	line = starting_map(vars);
	if (!line)
		return (1);
	vars->map->tab = tab_alloc(vars);
	if (!vars->map->tab)
		return (1);
	fill_tab(vars, &line);
	if (line)
		free(line);
	close(vars->map->fd);
	vars->map->fd = -1;
	vars->map->cp_tab = copy_map(vars);
	if (!vars->map->cp_tab)
		return (1);
	return (0);
}
