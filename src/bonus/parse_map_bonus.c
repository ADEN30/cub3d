/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:14:15 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/16 10:43:45 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	define_xy(t_vars *vars, char **line)
{
	int	x;
	int	y;
	int	xi;

	y = 0;
	xi = 0;
	x = ft_strlen(*line);
	while (*line && !line_isprint(*line))
	{
		xi = ft_strlen(*line);
		if (xi > x)
			x = xi;
		free(*line);
		*line = get_next_line(vars->map->fd);
		y++;
	}
	if (*line)
		free(*line);
	x -= 1;
	vars->map->x = x;
	vars->map->y = y;
	close(vars->map->fd);
	vars->map->fd = -1;
}

int	read_map_file(t_vars *vars, char *argv)
{
	char	*line;

	line = get_next_line(vars->map->fd);
	if (!line || !ft_strlen(line))
		return (print_error("Error : Empty file"));
	if (find_all_style(vars, &line))
		return (print_error("Error : Wrong or No or\
	Multiple information in the file"));
	if (check_assets(vars, &line))
		return (print_error("Error : Wrong asset(s) path(s)"));
	if (check_next_line(vars, &line))
		return (print_error("Error : No map definition in file"));
	define_xy(vars, &line);
	if (create_tab(vars, argv))
		return (print_error("Error : Map's tab could not be created"));
	if (check_map(vars))
		return (1);
	return (0);
}

int	parse_map(int argc, char *argv[], t_vars *vars)
{
	if (argc != 2)
		return (print_error("Error : Wrong number of arguments"));
	if (badmap(argv[1]))
		return (print_error("Error : No *.cub format"));
	vars->map = init_map();
	vars->style = init_style();
	if (!vars->map || !vars->style)
		return (print_error("Error :\
	Not enough memory for map and/or textures allocation"));
	vars->map->fd = open(argv[1], O_RDONLY);
	if (vars->map->fd < 0)
		return (print_error("Error : Can not open the map"));
	if (read_map_file(vars, argv[1]))
		return (1);
	return (0);
}
