/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:15:38 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/06 10:32:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!(*texture))
		return (1);
	return (0);
}

int	init_textures(t_vars *vars)
{
	t_images	*imgs;
	t_style		*style;

	style = vars->style;
	imgs = style->images;
	if (init(style->north_path, &imgs->north_texture)
		|| init(style->south_path, &imgs->south_texture)
		|| init(style->west_path, &imgs->west_texture)
		|| init(style->east_path, &imgs->east_texture))
		return (1);
	return (0);
}

int	init_player_textures(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map->y)
	{
		x = -1;
		while (++x < vars->map->x)
		{
			if (ft_strchr("NSEW", (char) vars->map->tab[y][x]))
			{
				vars->pers = init_pers(x * DIMENSION + (DIMENSION / 2),
						y * DIMENSION + (DIMENSION / 2),
						(char) vars->map->tab[y][x]);
				if (!vars->pers)
					return (print_error("Error : Can not generate a player\n"));
			}
		}
	}
	if (init_textures(vars))
		return (print_error("Error : Can not load textures\n"));
	return (0);
}

int	init_graphic(t_vars *vars)
{
	t_images	*img;

	img = vars->style->images;
	img->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	img->minimap = mlx_new_image(vars->mlx, vars->map->x * DIMENSION,
			vars->map->y * DIMENSION);
	img->rays = mlx_new_image(vars->mlx, vars->map->x * DIMENSION,
			vars->map->y * DIMENSION);
	img->charac = mlx_new_image(vars->mlx, vars->map->x * DIMENSION,
			vars->map->y * DIMENSION);
	if (!img->threed || !img->minimap || !img->rays || !img->charac)
		return (print_error("Error : Can not create a new image\n"));
	if (init_player_textures(vars))
		return (1);
	return (0);
}
