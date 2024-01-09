/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:00 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 15:59:01 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->tab = NULL;
	map->cp_tab = NULL;
	map->x = 0;
	map->y = 0;
	map->fd = -1;
	return (map);
}

static t_images	*init_images(void)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	if (!images)
		return (NULL);
	images->east_texture = NULL;
	images->north_texture = NULL;
	images->south_texture = NULL;
	images->west_texture = NULL;
	images->minimap = NULL;
	images->rays = NULL;
	images->threed = NULL;
	return (images);
}

t_style	*init_style(void)
{
	t_style	*style;

	style = malloc(sizeof(t_style));
	if (!style)
		return (NULL);
	style->images = init_images();
	if (!style->images)
		return (free(style), NULL);
	style->north_path = NULL;
	style->south_path = NULL;
	style->west_path = NULL;
	style->east_path = NULL;
	style->define_floor = 0;
	style->define_roof = 0;
	style->floor = 0;
	style->roof = 0;
	return (style);
}

t_pers	*init_pers(int x, int y, char c)
{
	t_pers	*pers;

	pers = malloc(sizeof(t_pers));
	if (!pers)
		return (NULL);
	pers->x = x;
	pers->y = y;
	pers->points = NULL;
	if (c == 'N')
		pers->angle = 90 * M_PI / 180;
	else if (c == 'S')
		pers->angle = 270 * M_PI / 180;
	else if (c == 'W')
		pers->angle = 180 * M_PI / 180;
	else if (c == 'E')
		pers->angle = 0;
	pers->deltax = cos(pers->angle);
	pers->deltay = sin(pers->angle);
	return (pers);
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->mlx = NULL;
	vars->map = NULL;
	vars->style = NULL;
	vars->pers = NULL;
	return (vars);
}
