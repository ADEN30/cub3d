/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:46 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/10 16:04:11 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars || parse_map(argc, argv, vars))
		return (free_vars(vars), 1);
	vars->mlx = mlx_init(1280, 720, "cub3d", true);
	if (!vars->mlx)
		return (free_vars(vars), 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (init_graphic(vars))
		return (free_vars(vars), 1);
	//if (show_minimap(vars))
		//return (free_vars(vars), 1);
	find_wall(vars);
	//rays_on_minimap(vars);
	show_view(vars);
	//mlx_mouse_hook(vars->mlx, mouse, vars);
	mlx_loop_hook(vars->mlx, move, vars);
	mlx_loop(vars->mlx);
	return (free_vars(vars), 0);
}
