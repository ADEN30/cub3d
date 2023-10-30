/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:50:05 by eberger           #+#    #+#             */
/*   Updated: 2023/08/04 14:50:26 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars || create_map(argc, argv, vars))
		return (free_vars(vars), system("leaks cub3d"), 1);
	vars->mlx = mlx_init(1500, 1500, "cub3d", true);
	if (!vars->mlx)
		return (free_vars(vars), system("leaks cub3d"), 1);
	if (show_map(vars) || init_3d(vars))
		return (free_vars(vars), system("leaks cub3d"), 1);
	
	ft_raycasting(vars);
//	mlx_loop_hook(vars->mlx, ft_raycasting, vars);
	if (MAP == 0)
		mlx_loop_hook(vars->mlx, show_vue, vars);
	mlx_loop_hook(vars->mlx, ft_hook_move, vars);
	mlx_loop(vars->mlx);
	return (free_vars(vars), system("leaks cub3d"), 0);
}

/*TOBEDONE:
 * */
