/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:15:38 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/14 15:23:15 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	define_speed(t_vars *vars)
{
	if (vars->dim == 64)
		vars->spd = 5;
	else if (vars->dim == 128)
		vars->spd = 10;
	else if (vars->dim == 256)
		vars->spd = 20;
}

int check_dimensions(t_vars *vars)
{
	t_images	*imgs;

	imgs = vars->style->images;
	if (imgs->north_texture->width != imgs->north_texture->height)
		return (1);
	if (imgs->north_texture->width != imgs->south_texture->width
		|| imgs->north_texture->height != imgs->south_texture->height)
		return (1);
	if (imgs->north_texture->width != imgs->west_texture->width
		|| imgs->north_texture->height != imgs->west_texture->height)
		return (1);
	if (imgs->north_texture->width != imgs->east_texture->width
		|| imgs->north_texture->height != imgs->east_texture->height)
		return (1);
	vars->dim = imgs->north_texture->width;
	vars->ratio = 0.8215 / vars->dim;
	define_speed(vars);
	return (0);	
}
