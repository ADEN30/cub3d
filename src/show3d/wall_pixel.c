/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:37:09 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/10 12:36:37 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint8_t	*get_pixel_north(t_vars *vars, mlx_texture_t *north, t_point *point,
	double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)north->height / point->h) * y;
	y_pixel_t = (int)point->x % vars->dim;
	pixel_position_t = ((int)x_pixel_t * north->width + (int)y_pixel_t);
	pixel_color = &((north->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_south(t_vars *vars, mlx_texture_t *south, t_point *point,
	double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)south->height / point->h) * y;
	y_pixel_t = ((int)point->x % vars->dim);
	pixel_position_t = ((int)x_pixel_t * south->width - (int)y_pixel_t);
	if (pixel_position_t < 0)
		pixel_position_t = pixel_position_t * -1;
	pixel_color = &((south->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_east(t_vars *vars, mlx_texture_t *east, t_point *point,
	double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)east->height / point->h) * y;
	y_pixel_t = ((int)point->y % vars->dim);
	pixel_position_t = ((int)x_pixel_t * east->width + (int)y_pixel_t);
	pixel_color = &((east->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_west(t_vars *vars, mlx_texture_t *west, t_point *point,
	double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)west->height / point->h) * y;
	y_pixel_t = ((int)point->y % vars->dim);
	pixel_position_t = ((int)x_pixel_t * west->width) - (int)y_pixel_t;
	if (pixel_position_t < 0)
		pixel_position_t = pixel_position_t * -1;
	pixel_color = &((west->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint32_t	get_pixel(t_vars *vars, t_point *point, int y)
{
	int			r;
	int			g;
	int			b;
	uint8_t		*pixel;
	t_images	*img;

	pixel = NULL;
	img = vars->style->images;
	y = y - ((MAX_HEIGHT / 2) - (point->h / 2));
	if (y == point->h)
		y = y - 1;
	if (point->face == 'N')
		pixel = get_pixel_north(vars, img->north_texture, point, y);
	else if (point->face == 'S')
		pixel = get_pixel_south(vars, img->south_texture, point, y);
	else if (point->face == 'E')
		pixel = get_pixel_east(vars, img->east_texture, point, y);
	else if (point->face == 'W')
		pixel = get_pixel_west(vars, img->west_texture, point, y);
	r = *(pixel++);
	g = *(pixel++);
	b = *(pixel++);
	return (get_rgba(r, g, b, 255));
}
