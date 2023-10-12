/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:46:58 by eberger           #+#    #+#             */
/*   Updated: 2023/08/04 14:32:48 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	if (map->lines)
		ft_lstclear(&map->lines, &free);
	free(map);
}

static void	free_style(t_style *style)
{
	if (style->north_path)
		free(style->north_path);
	if (style->south_path)
		free(style->south_path);
	if (style->west_path)
		free(style->west_path);
	if (style->east_path)
		free(style->east_path);
	if (style->images)
		free(style->images);
	free(style);
}

 void	free_rays(t_ray **rays, t_vars *vars)
{
	int	i;
	(void)vars;

	i = 0;
	while (rays[i])
	{
		free(rays[i]);
		if (rays[i]->count_points)
			free(rays[i]->points);
		i++;
	}
	free(rays);
}

static void	free_pers(t_pers *pers, t_vars *vars)
{
	free_rays(pers->rays, vars);
	free(pers);
}

void	free_vars(t_vars *vars)
{
	if (vars)
	{
		if (vars->mlx)
			mlx_terminate(vars->mlx);
		if (vars->map)
			free_map(vars->map);
		if (vars->style)
			free_style(vars->style);
		if (vars->pers)
			free_pers(vars->pers, vars);
		free(vars);
	}
}
