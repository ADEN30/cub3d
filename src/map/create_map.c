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

int check_assets(t_vars *vars)
{
	int fd[4];

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
	return (1);	
}

int	read_map_file(t_vars *vars, char *argv)
{
	char	*line;

	line = get_next_line(vars->map->fd);
	if (!line || !ft_strlen(line))
		return (print_error("Error : The map is empty"));
	if (find_all_style(vars, &line))
		return (print_error("Error : Wrong information on the file"));
	if (check_assets(vars))
		return (print_error("Error : Wrong asset(s) path(s)"));
	if (create_tab(vars, &line, argv))
		return (print_error("Error : 2D tab could not be generated"));
	if (check_map(vars))
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
	if (read_map_file(vars, argv[1]))
		return (1);
	return (0);
}
