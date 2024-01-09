/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:11 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 15:59:13 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
				vars->pers = init_pers(x * MINI + (MINI / 2),
						y * MINI + (MINI / 2),
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

static int	new_image(t_vars *vars, mlx_image_t **image)
{
	if (vars->map->y * MINI > MAX_HEIGHT)
		return (print_error("Error : Map is too high\n"));
	if (vars->map->x * MINI > MAX_WIDTH)
		return (print_error("Error : Map is too large\n"));
	else
	{
		*image = mlx_new_image(vars->mlx, vars->map->x * MINI,
				vars->map->y * MINI);
		if (!(*image))
			return (print_error("Error : Can not create a new image\n"));
	}
	return (0);
}

int	init_graphic(t_vars *vars)
{
	t_images	*img;

	img = vars->style->images;
	img->threed = mlx_new_image(vars->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (new_image(vars, &img->minimap) || new_image(vars, &img->rays))
		return (1);
	if (!img->threed)
		return (print_error("Error : Can not create a new image\n"));
	if (init_player_textures(vars))
		return (1);
	return (0);
}
