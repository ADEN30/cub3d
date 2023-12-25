#include "../../include/cub3d.h"

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

void	fill_tab(t_vars *vars, int x)
{
	t_list *lst;
	char	*tab;
	int		i;
	int		j;

	j = 0;
	tab = NULL;
	lst = vars->map->lines;
	while (lst)
	{
		i = 0;
		tab = (char *)lst->content;
		while (tab[i] && i < x)
		{
			vars->map->tab[j][i] = tab[i];
			i++;
		}
		lst = lst->next;
		j++;
	}
}

int **tab_alloc(int x, int y)
{
	int	**tab;
	int		i;

	i = 0;
	tab = malloc(y * sizeof(int *));
	if (tab == NULL)
		return (NULL);
	while (i < y)
	{
		tab[i] = malloc(x * sizeof(int));
		if (tab[i] == NULL)
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

int	create_tab(t_vars *vars)
{
	t_list	*lst;
	int		x;
	int		y;

	lst = vars->map->lines;
	x = y = 0;
	while (lst)
	{
		if (x < (int)ft_strlen((char *)(lst->content)))
			x = (int)ft_strlen((char *)lst->content);
		y++;
		lst = lst->next;
	}
	vars->map->tab = tab_alloc(x, y);
	if (!vars->map->tab)
		return (1);
	fill_tab(vars, x);
	return (0);
}
