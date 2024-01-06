/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:43:41 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/06 15:54:58 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_map(t_map *map)
{
	if (map->cp_tab)
	{
		while (map->y > 0)
			free(map->cp_tab[--map->y]);
		free(map->cp_tab);
	}
	if (map->tab)
	{
		while (map->y > 0)
			free(map->tab[--map->y]);
		free(map->tab);
	}
	free(map);
}

static void	free_textures(t_images *images, mlx_t *mlx)
{
	if (images)
	{
		if (images->north_texture)
			mlx_delete_texture(images->north_texture);
		if (images->south_texture)
			mlx_delete_texture(images->south_texture);
		if (images->west_texture)
			mlx_delete_texture(images->west_texture);
		if (images->east_texture)
			mlx_delete_texture(images->east_texture);
		if (images->minimap)
			mlx_delete_image(mlx, images->minimap);
		if (images->rays)
			mlx_delete_image(mlx, images->rays);
		if (images->charac)
			mlx_delete_image(mlx, images->charac);
		if (images->threed)
			mlx_delete_image(mlx, images->threed);
		free(images);
	}
}

static void	free_style(t_style *style, mlx_t *mlx)
{
	if (style)
	{
		free_textures(style->images, mlx);
		if (style->north_path)
			free(style->north_path);
		if (style->south_path)
			free(style->south_path);
		if (style->west_path)
			free(style->west_path);
		if (style->east_path)
			free(style->east_path);
		free(style);
	}
}

static void	free_pers(t_pers *pers)
{
	if (pers->points)
		free(pers->points);
	free(pers);
}

void	free_vars(t_vars *vars)
{
	if (vars)
	{
		if (vars->map)
			free_map(vars->map);
		if (vars->style)
			free_style(vars->style, vars->mlx);
		if (vars->pers)
			free_pers(vars->pers);
		if (vars->mlx)
			mlx_terminate(vars->mlx);
		free(vars);
	}
}
