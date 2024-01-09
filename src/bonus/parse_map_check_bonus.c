/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:14:46 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 16:02:44 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_next_line(t_vars *vars, char **line)
{
	if (!*line)
		return (1);
	while (*line)
	{
		if (line_isprint(*line))
		{
			free(*line);
			*line = get_next_line(vars->map->fd);
		}
		else
			break ;
	}
	if (!*line)
		return (1);
	return (0);
}

int	check_assets(t_vars *vars, char **line)
{
	int	fd[4];

	fd[0] = open(vars->style->north_path, O_RDONLY);
	fd[1] = open(vars->style->north_path, O_RDONLY);
	fd[2] = open(vars->style->north_path, O_RDONLY);
	fd[3] = open(vars->style->north_path, O_RDONLY);
	if (fd[0] != -1 && fd[1] != -1 && fd[2] != -1 && fd[3] != -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		close(fd[3]);
		return (0);
	}
	if (*line)
		free(*line);
	return (1);
}

int	badmap(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len == 4)
		return (1);
	if (ft_strncmp(file + (len - 4), ".cub", 4))
		return (1);
	return (0);
}
