#include "../../include/cub3d.h"

void	print_error_red(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd("Erreur : ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
}

int	print_error(char *str)
{
	print_error_red(str);
	ft_putendl_fd("Pour que le programme fonctionne, procédé comme cela:", 1);
	ft_putendl_fd("./cub3d map.cub", 1);
	return (1);
}
