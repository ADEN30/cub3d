#include "../../include/cub3d.h"

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

int	line_isprint(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isprint(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	create_list(t_vars *vars, char **line)
{
	t_list	*lst;

	lst = NULL;
	if (!*line)
		return (1);
	while (line_isprint(*line))
	{
		free(*line);
		*line = get_next_line(vars->map->fd);
	}
	while (*line && !line_isprint(*line))
	{
		(*line)[ft_strlen(*line) - 1] = 0;
		if (lst)
			ft_lstadd_back(&lst, ft_lstnew(*line));
		else
			lst = ft_lstnew(*line);
		*line = get_next_line(vars->map->fd);
	}
	if (*line)
		free(*line);
	vars->map->lines = lst;
	return (0);
}

int check_assets(t_vars *vars)
{
	if (open(vars->style->north_path, O_RDONLY) != -1
		&& open(vars->style->south_path, O_RDONLY) != -1
		&& open(vars->style->east_path, O_RDONLY) != -1 
		&& open(vars->style->west_path, O_RDONLY) != -1)
		return (0);
	return (1);	
}

int	read_map_file(t_vars *vars)
{
	char	*line;

	line = get_next_line(vars->map->fd);
	if (!line || !ft_strlen(line))
		return (print_error("Error : The map is empty"));
	if (find_all_style(vars, &line))
		return (print_error("Error : Wrong information on the file"));
	if (check_assets(vars))
		return (print_error("Error : Wrong asset(s) path(s)"));
	if (create_list(vars, &line))
		return (print_error("Error : 2D map could not be generated"));
	if (test_map(vars))
		return (1);
	return (0);
}

int	create_map(int argc, char *argv[], t_vars *vars)
{
	if (argc != 2)
		return (print_error("Error : Wrong number of arguments"));
	if (badmap(argv[1]))
		return (print_error("Error : No *.cub format"));
	vars->map = init_map();
	vars->style = init_style();
	if (!vars->map || !vars->style)
		return (print_error("Error : Not enough memory for map and/or textures allocation"));
	vars->map->fd = open(argv[1], O_RDONLY);
	if (vars->map->fd < 0)
		return (print_error("Error : Can not open the map"));
	if (read_map_file(vars))
		return (1);
	return (0);
}
