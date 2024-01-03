#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars || create_map(argc, argv, vars))
		return (free_vars(vars), 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	vars->mlx = mlx_init(800, 600, "cub3d", true);
	if (!vars->mlx)
		return (free_vars(vars), 1);
	if (init_player_textures(vars))
		return (free_vars(vars), 1);
	find_wall(vars);
	show_view(vars);
	mlx_loop_hook(vars->mlx, ft_move, vars);
	mlx_loop(vars->mlx);
	//mlx_terminate(vars->mlx);
	return (free_vars(vars), 0);
}
