/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_style3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:45:26 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/16 10:47:22 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	found_color(char **split, t_vars *vars, int *value)
{
	int	i;

	i = 0;
	while (split[i])
	{
		value[i] = ft_atoi(split[i]);
		if (value[i] < 0 || value[i] > 255)
		{
			print_error("Error : Wrong information of color definition");
			free_vars(vars);
			exit(1);
		}
		i++;
	}
}

uint32_t	define_color(char *line, t_vars *vars)
{
	char	**split;
	int		value[3];
	int		i;

	i = 0;
	while (*line == ' ')
		line++;
	split = ft_split(line, ',');
	if (!split)
	{
		print_error("Error : Malloc failed at color definition");
		free_vars(vars);
		exit(1);
	}
	while (split[i])
		i++;
	if (i != 3)
	{
		print_error("Error : Wrong information of color definition");
		free_vars(vars);
		exit(1);
	}
	found_color(split, vars, value);
	free_split(split);
	return (get_rgba(value[0], value[1], value[2], 255));
}
