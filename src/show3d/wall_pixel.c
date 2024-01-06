/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:37:09 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/05 12:37:11 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint8_t	*get_pixel_north(t_vars *vars, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->north_texture->height / point->h) * y;
	y_pixel_t = (double)vars->style->images->north_texture->width / 10 * ((int)point->x % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->north_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->north_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_south(t_vars *vars, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->south_texture->height / point->h) * y;
	y_pixel_t = (double)vars->style->images->south_texture->width / 10 * ((int)point->x % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->south_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->south_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_east(t_vars *vars, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->east_texture->height / point->h) * y;
	y_pixel_t = (double)vars->style->images->east_texture->width / 10 * ((int)point->y % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->east_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->east_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_west(t_vars *vars, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->west_texture->height / point->h) * y;
	y_pixel_t = (double)vars->style->images->west_texture->width / 10 * ((int)point->y % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->west_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->west_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint32_t	get_pixel(t_vars *vars, t_point *point, int y)
{
	int		r;
	int		g;
	int		b;
	uint8_t	*pixel;

	pixel = NULL;
	y = y - ((vars->mlx->height - point->h) / 2);
	if (y == point->h)
		y = y - 1;
	if (point->face == 'N')
		pixel = get_pixel_north(vars, point, y);
	else if (point->face == 'S')
		pixel = get_pixel_south(vars, point, y);
	else if (point->face == 'E')
		pixel = get_pixel_east(vars, point, y);
	else if (point->face == 'W')
		pixel = get_pixel_west(vars, point, y);
	r = *(pixel++);
	g = *(pixel++);
	b = *(pixel++);
	return (get_rgba(r, g, b, 255));
}
