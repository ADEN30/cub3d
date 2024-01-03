/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:19 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/02 19:52:32 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

void	print_rays_on_minimap(t_vars* vars)
{
	int			i;
	int32_t		rays;

	i = 799;
	rays = mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	if (rays == -1)
	{
		print_error("Error while printing rays on minimap\n");
		free_vars(vars);
		exit(1);
	}
    mlx_put_pixel(vars->pers->rays[0]->img, vars->pers->x, vars->pers->y,
		get_rgba(255, 0, 0, 255));
	while (i >= 0)
	{
        mlx_put_pixel(vars->pers->rays[0]->img,
			round(vars->pers->rays[0]->points[i].x),
			round(vars->pers->rays[0]->points[i].y),
			get_rgba(255, 0, 0, 255));
        i--;
	}
}

int	print_case(t_vars *vars, mlx_image_t **img, uint32_t color, int *xy)
{
	if (!*img)
	{
		*img = mlx_new_image(vars->mlx, DIMENSION, DIMENSION);
		if (!*img)
		{
			print_error("Error while creating image\n");
			free_vars(vars);
			exit(1);
		}
	}
	if (mlx_image_to_window(vars->mlx, vars->style->images->wall_image,
		xy[0] * DIMENSION, xy[1] * DIMENSION) == -1)
	{
		print_error("Error while printing image\n");
		free_vars(vars);
		exit(1);
	}
	put_pixels(*img, color);
	return (0);
}

int	which_case(t_vars *vars, int *xy)
{
	if (vars->map->tab[xy[1]][xy[0]] == 1)
	{
		if (print_case(vars, &(vars->style->images->wall_image),
			get_rgba(0, 0, 0, 255), xy))
			return (1);
	}
	else if (vars->map->tab[xy[1]][xy[0]] == 0)
	{
		if (print_case(vars, &(vars->style->images->wall_image),
			get_rgba(255, 255, 255, 255), xy))
			return (1);
	}
	return (0);
}

void	show_minimap(t_vars *vars)
{
	int		xy[2];

	xy[1] = -1;
	while (++(xy[1]) < vars->map->Y)
	{
		xy[0] = -1;
		while (++(xy[0]) < vars->map->X)
		{
			if (which_case(vars, xy))
			{
				print_error("Error while printing minimap\n");
				free_vars(vars);
				exit(1);
			}
		}
	}
	print_rays_on_minimap(vars);
}
