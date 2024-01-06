/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_style.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:45:18 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/06 15:45:19 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	init_checkstyle(int *check)
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

	init_checkstyle(check);
	while (*line)
	{
		if (line_isprint(*line))
		{
			free(*line);
			*line = get_next_line(vars->map->fd);
		}
		else if (!find_style(*line, vars, check))
		{
			free(*line);
			*line = get_next_line(vars->map->fd);
			if (!check_config(vars))
				break ;
		}
		else
			return (1);
	}
	return (0);
}
