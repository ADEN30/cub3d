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
		print_error("Error : Wrong color definition\n");
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

int	last_style(char *line, t_vars *vars, int *check)
{
	if (!ft_strncmp(line, "F ", 2) && !vars->style->define_floor)
	{
		if (check[4] == 0)
		{
			vars->style->floor = define_color(line + 2, vars);
			vars->style->define_floor = 1;
			check[4] = 1;
			return (0);
		}
		else
			return (1);
	}
	else if (!ft_strncmp(line, "C ", 2) && !vars->style->define_roof)
	{
		if (check[5] == 0)
		{
			vars->style->roof = define_color(line + 2, vars);
			vars->style->define_roof = 1;
			check[5] = 1;
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

int	next_style(char *line, t_vars *vars, int *check)
{
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (check[2] == 0)
		{
			vars->style->west_path = define_image_path(line + 2);
			check[2] = 1;
			return (0);
		}
		else
			return (1);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (check[3] == 0)
		{
			vars->style->east_path = define_image_path(line + 2);
			check[3] = 1;
			return (0);
		}
		else
			return (1);
	}
	else
		return(last_style(line, vars, check));
}

int	find_style(char *line, t_vars *vars, int *check)
{
	while (line && *line && *line == ' ')
		line++;
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (check[0] == 0)
		{
			vars->style->north_path = define_image_path(line + 2);
			check[0] = 1;
			return (0);
		}
		else
			return (1);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (check[1] == 0)
		{
			vars->style->south_path = define_image_path(line + 2);
			check[1] = 1;
			return (0);
		}
		else
			return (1);
	}
	return (next_style(line, vars, check));
}