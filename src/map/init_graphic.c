/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:15:38 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/10 09:13:09 by jmathieu         ###   ########.fr       */
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
	if (init_textures(vars))
		return (print_error("Error : Can not load textures\n"));
	if (check_dimensions(vars))
		return (print_error("Error : Textures sizes are not identical\n"));
	while (++y < vars->map->y)
	{
		x = -1;
		while (++x < vars->map->x)
		{
			if (ft_strchr("NSEW", (char) vars->map->tab[y][x]))
			{
				vars->pers = init_pers(x * vars->dim + (vars->dim / 2),
						y * vars->dim + (vars->dim / 2),
						(char) vars->map->tab[y][x]);
				if (!vars->pers)
					return (print_error("Error : Can not generate a player\n"));
			}
		}
	}
	return (0);
}

int	init_graphic(t_vars *vars)
{
	t_images	*img;

	img = vars->style->images;
	img->threed = mlx_new_image(vars->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (!img->threed)
		return (print_error("Error : Can not create a new image\n"));
	if (init_player_textures(vars))
		return (1);
	return (0);
}
