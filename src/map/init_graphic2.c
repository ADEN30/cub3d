/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:15:38 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/10 11:46:07 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	define_ratio(t_vars *vars)
{
	if (vars->dim == 64)
		vars->ratio = 0.0125;
	else if (vars->dim == 128)
		vars->ratio = 0.01;
	else if (vars->dim == 256)
		vars->ratio = 0.005;
}

static void	define_speed(t_vars *vars)
{
	if (vars->dim == 16)
		vars->spd = 0.2;
	else if (vars->dim == 32)
		vars->spd = 0.4;
	else if (vars->dim == 64)
		vars->spd = 0.8;
	else if (vars->dim == 128)
		vars->spd = 1.6;
	else if (vars->dim == 256)
		vars->spd = 3.2;
}

int check_dimensions(t_vars *vars)
{
	t_images	*imgs;

	imgs = vars->style->images;
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
	define_ratio(vars);
	define_speed(vars);
	return (0);	
}
