#include "../../include/cub3d.h"

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

static uint32_t	define_color(char *line, t_vars *vars)
{
	int	value[3];
	int	i;

	i = 0;
	while (*line == ' ')
		line++;
	if (check_line(line))
	{
		print_error("Les informations de la map sont incorrectes\n");
		free_vars(vars);
		exit(1);
	}
	while (i < 3)
	{
		value[i] = value_rgb(line, vars);
		while (*line && *line != ',')
			line++;
		line++;
		i++;
	}
	return (get_rgba(value[0], value[1], value[2], 255));
}

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

static int	find_style(char *line, t_vars *vars)
{
	while (line && *line && *line == ' ')
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		vars->style->north_path = define_image_path(line + 2);
	else if (!ft_strncmp(line, "SO ", 3))
		vars->style->south_path = define_image_path(line + 2);
	else if (!ft_strncmp(line, "WE ", 3))
		vars->style->west_path = define_image_path(line + 2);
	else if (!ft_strncmp(line, "EA ", 3))
		vars->style->east_path = define_image_path(line + 2);
	else if (!ft_strncmp(line, "F ", 2) && !vars->style->define_floor)
	{
		vars->style->floor = define_color(line + 2, vars);
		vars->style->define_floor = 1;
	}
	else if (!ft_strncmp(line, "C ", 2) && !vars->style->define_roof)
	{
		vars->style->roof = define_color(line + 2, vars);
		vars->style->define_roof = 1;
	}
	return (0);
}

int	find_all_style(t_vars *vars, char **line)
{
	while (*line && check_config(vars))
	{
		find_style(*line, vars);
		free(*line);
		*line = get_next_line(vars->map->fd);
	}
	return (0);
}
