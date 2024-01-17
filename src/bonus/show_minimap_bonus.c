/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:19 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/17 14:12:05 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	put_pixels_dimension(t_vars *vars, int x, int y, uint32_t color)
{
	t_images	*img;
	int			xi;
	int			yi;

	img = vars->style->images;
	yi = y * 4;
	while (yi < (y + 1) * 4)
	{
		xi = x * 4;
		while (xi < (x + 1) * 4)
		{
			mlx_put_pixel(img->threed, xi, yi, color);
			xi++;
		}
		yi++;
	}
}

static void	which_case(t_vars *vars, int x, int y)
{
	int			i;

	i = vars->map->tab[y][x];
	if (i == (int) '1')
		put_pixels_dimension(vars, x, y, get_rgba(150, 150, 150, 100));
	else if (i == (int) '0' || i == (int) 'N'
		|| i == (int) 'S' || i == (int) 'E'
		|| i == (int) 'W')
		put_pixels_dimension(vars, x, y, get_rgba(255, 255, 255, 200));
	else if (i == (int) ' ')
		put_pixels_dimension(vars, x, y, get_rgba(0, 0, 0, 50));
}

void	show_minimap(t_vars *vars)
{
	int			x;
	int			y;

	y = -1;
	while (++y < vars->map->y)
	{
		x = -1;
		while (++x < vars->map->x)
			which_case(vars, x, y);
	}
}
