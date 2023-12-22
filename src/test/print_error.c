#include "../../include/cub3d.h"

int	print_error(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	return (1);
}
