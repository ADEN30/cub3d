#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars || create_map(argc, argv, vars))
		return (free_vars(vars), system("leaks cub3d"));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	vars->mlx = mlx_init(1500, 1500, "cub3d", true);
	if (!vars->mlx)
		return (free_vars(vars), system("leaks cub3d"));
	if (show_map(vars))
		return (free_vars(vars), system("leaks cub3d"));
	init_3d(vars);
	change_plan(vars);
	create_vue(vars);
	//mlx_loop_hook(vars->mlx, ft_raycasting, vars);
	//if (MAP == 0)
		//mlx_loop_hook(vars->mlx, show_vue, vars);
//	show_vue(vars);
	mlx_loop_hook(vars->mlx, ft_hook_move, vars);
	mlx_loop(vars->mlx);
	return (free_vars(vars), system("leaks cub3d"));
}

/*TOBEDONE:
 * */
