/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:49:49 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/16 10:45:24 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	flood_fill(t_vars *vars, int x, int y, int i)
{
	static int	end = 0;

	if (x < 0 || x >= vars->map->x || y < 0 || y >= vars->map->y
		|| vars->map->cp_tab[y][x] == (int) ' ')
	{
		end++;
		return (end);
	}
	if (vars->map->cp_tab[y][x] == (int) '1'
		|| vars->map->cp_tab[y][x] == (int) '*')
		return (end);
	vars->map->cp_tab[y][x] = (int) '*';
	flood_fill(vars, x + 1, y, i);
	flood_fill(vars, x - 1, y, i);
	flood_fill(vars, x, y + 1, i);
	flood_fill(vars, x, y - 1, i);
	return (end);
}

static int	check_map_floodfill(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map->y)
	{
		x = -1;
		while (++x < vars->map->x)
		{
			if (ft_strchr("0", (char) vars->map->cp_tab[y][x]))
			{
				if (flood_fill(vars, x, y, (int) '*'))
					return (print_error("Error : Map is not closed"));
			}
		}
	}
	return (0);
}

static int	startpoint(t_vars *vars, int x, int y, int *start)
{
	++(*start);
	if (*start > 1)
		return (print_error("Error : Wrong number of player(s)"));
	vars->map->cp_tab[y][x] = (int) '0';
	return (0);
}

int	check_map(t_vars *vars)
{
	int	x;
	int	y;
	int	start;

	y = -1;
	start = 0;
	while (++y < vars->map->y)
	{
		x = -1;
		while (++x < vars->map->x)
		{
			if (ft_strchr("NSEW", (char) vars->map->cp_tab[y][x]))
			{
				if (startpoint(vars, x, y, &start))
					return (1);
			}
			else if (!ft_strchr("01NSEW ", (char) vars->map->cp_tab[y][x]))
				return (print_error("Error : Wrong map characters detected"));
		}
	}
	if (check_map_floodfill(vars))
		return (1);
	return (0);
}
