/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:49:58 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/17 11:39:41 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars || parse_map(argc, argv, vars))
		return (free_vars(vars), 1);
	vars->mlx = mlx_init(MAX_WIDTH, MAX_HEIGHT, "cub3D", true);
	if (!vars->mlx)
		return (free_vars(vars), 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (init_graphic(vars))
		return (free_vars(vars), 1);
	find_wall(vars);
	show_view(vars);
	mlx_loop_hook(vars->mlx, move, vars);
	mlx_loop(vars->mlx);
	return (free_vars(vars), 0);
}
