/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:19 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/06 16:21:17 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	put_pixels_dimension(t_vars *vars, int x, int y, uint32_t color)
{
	t_images	*img;
	int xi;
	int yi;

	img = vars->style->images;
	yi = y * DIMENSION;
	while (yi < (y * DIMENSION) + DIMENSION)
	{
		xi = x * DIMENSION;
		while (xi < (x * DIMENSION) + DIMENSION)
		{
			mlx_put_pixel(img->minimap, xi, yi, color);
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

int	show_minimap(t_vars *vars)
{
	int32_t		cs;
	t_images	*img;
	int			x;
	int			y;

	y = -1;
	img = vars->style->images;
	while (++y < vars->map->y)
	{
		x = -1;
		while (++x < vars->map->x)
			which_case(vars, x, y);
	}
	cs = mlx_image_to_window(vars->mlx, img->minimap, 0, 0);
	if (cs == -1)
		return (print_error("Error : Map can not be generated\n"), 1);
	return (0);
}
