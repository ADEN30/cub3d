/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:15:38 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/17 12:14:06 by jmathieu         ###   ########.fr       */
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

static int	init_textures(t_vars *vars)
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

static int	minimap_dimensions(t_vars *vars)
{
	if (vars->map->x > 50
		|| vars->map->y > 50)
		return (print_error("Error\nMap is too big,\
	it can not be generated"));
	return (0);
}

int	init_player_textures(t_vars *vars)
{
	int	xy[2];

	xy[1] = -1;
	if (init_textures(vars))
		return (print_error("Error\nCan not load textures"));
	if (minimap_dimensions(vars))
		return (1);
	while (++xy[1] < vars->map->y)
	{
		xy[0] = -1;
		while (++xy[0] < vars->map->x)
		{
			if (ft_strchr("NSEW", (char) vars->map->tab[xy[1]][xy[0]]))
			{
				vars->pers = init_pers((double) xy[0] + 0.5, (double)
					xy[1] + 0.5, (char) vars->map->tab[xy[1]][xy[0]]);
				if (!vars->pers)
					return (print_error("Error\nCan not generate a player"));
			}
		}
	}
	return (0);
}

int	init_graphic(t_vars *vars)
{
	t_images	*img;
	int32_t		cs;

	img = vars->style->images;
	img->threed = mlx_new_image(vars->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (!img->threed)
		return (print_error("Error\nCan not create a new image"));
	if (init_player_textures(vars))
		return (1);
	cs = mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
	if (cs == -1)
		return (print_error("Error\nCan not print pixels"));
	return (0);
}
