/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:00:16 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 16:00:18 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mouse(void *param)
{
	t_vars	*vars;

	vars = param;
	(void)vars;
	//typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);
	//mlx_get_mouse_pos(vars->mlx, &vars->pers->x, &vars->pers->y);
}
