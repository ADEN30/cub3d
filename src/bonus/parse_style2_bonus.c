/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_style2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:45:26 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 16:02:29 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*define_image_path(char *line)
{
	int		len;
	char	*ret;

	while (*line == ' ')
		line++;
	len = ft_strlen(line);
	line[len - 1] = 0;
	ret = ft_strdup(line);
	return (ret);
}

static int	found_style_color(t_vars *vars, char *line, int *check, int i)
{
	uint32_t	*color;
	int		 	*define;

	if (i == 4)
	{
		color = &vars->style->floor;
		define = &vars->style->define_floor;
	}
	else if (i == 5)
	{
		color = &vars->style->roof;
		define = &vars->style->define_roof;
	}
	if (check[i] == 0)
	{
		*color = define_color(line + 2, vars);
		*define = 1;
		check[i] = 1;
		return (0);
	}
	else
		return (1);
}

static int	found_style_path(t_vars *vars, char *line, int *check, int i)
{
	char **path;

	if (i == 0)
		path = &vars->style->north_path;
	else if (i == 1)
		path = &vars->style->south_path;
	else if (i == 2)
		path = &vars->style->west_path;
	else if (i == 3)
		path = &vars->style->east_path;
	if (check[i] == 0)
	{
		*path = define_image_path(line + 2);
		check[i] = 1;
		return (0);
	}
	else
		return (1);
}

int	find_style(char *line, t_vars *vars, int *check)
{
	while (line && *line && *line == ' ')
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (found_style_path(vars, line, check, 0));
	else if (!ft_strncmp(line, "SO ", 3))
		return (found_style_path(vars, line, check, 1));
	else if (!ft_strncmp(line, "WE ", 3))
		return (found_style_path(vars, line, check, 2));
	else if (!ft_strncmp(line, "EA ", 3))
		return (found_style_path(vars, line, check, 3));
	else if (!ft_strncmp(line, "F ", 2) && !vars->style->define_floor)
		return (found_style_color(vars, line, check, 4));
	else if (!ft_strncmp(line, "C ", 2) && !vars->style->define_roof)
		return (found_style_color(vars, line, check, 5));
	return (1);
}
