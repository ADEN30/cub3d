/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:15:14 by eberger           #+#    #+#             */
/*   Updated: 2023/07/26 13:35:02 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	badmap(char *file)
{
	int	len;

	len = ft_strlen(file);
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
	while ((!*line || line_isprint(*line)))
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

int	read_map_file(t_vars *vars)
{
	char	*line;

	line = get_next_line(vars->map->fd);
	if (!line || !ft_strlen(line))
		return (print_error("Le fichier map est vide"));
	if (find_all_style(vars, &line))
		return (print_error("Erreur de fichier "));
	if (create_list(vars, &line))
		return (print_error("Erreur lors de la creation de la map"));
	if (test_map(vars))
		return (1);
	return (0);
}

int	create_map(int argc, char *argv[], t_vars *vars)
{
	if (argc != 2)
		return (print_error("Nombre d'arguments incorrects"));
	if (badmap(argv[1]))
		return (print_error("Seul les fichiers .cub sont acceptes"));
	vars->map = init_map();
	vars->style = init_style();
	if (!vars->map || !vars->style)
		return (print_error("Probleme dans la gestion de la memoire"));
	vars->map->fd = open(argv[1], O_RDONLY);
	if (vars->map->fd < 0)
		return (print_error("Impossible d'ouvrir le fichier en argument"));
	if (read_map_file(vars))
		return (1);
	return (0);
}
