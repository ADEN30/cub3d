/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_pixel_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:37:09 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/09 13:53:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint8_t	*get_pixel_north(mlx_texture_t *north, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;
	(void)y_pixel_t;
	(void) y;
	x_pixel_t = ((int)(point->x * 16) % 128 * 4);
	//y_pixel_t = ((int)(point->y * 16) / 128) * 4;
	y_pixel_t = /*(int)point->h / 720 +*/ point->test/*- ((int)point->h / 720 * 128)*/;
	//printf("y = %f\n", y);
	//printf("test: %d\n", point->test / 128 /4);
	pixel_position_t = (((int)x_pixel_t + (int)y_pixel_t));
	//printf("piel_position: %d\n", pixel_position_t );
	//printf("piel_position[%d]: %d\n", pixel_position_t, north->pixels[pixel_position_t] );
	//printf("piel_position[%d]: %d\n", pixel_position_t + 1, north->pixels[pixel_position_t + 1] );
	if (pixel_position_t / 128 / 4 < 128 )
	{
		//printf("GOOD\n");
		pixel_color = &((north->pixels)[pixel_position_t]);
	}
	else
	{
		point->test = 0;
		y_pixel_t = point->test;
		pixel_position_t = (((int)x_pixel_t + (int)y_pixel_t));
		pixel_color = &((north->pixels)[pixel_position_t]);
	}
	/*else
	{
		x_pixel_t = ((double)north->width / point->h) * y;
		y_pixel_t = ((int)point->x % MINI);
		pixel_position_t = ((int)x_pixel_t * north->width + (int)y_pixel_t);
		//printf("piel_position[%d]: %d\n", pixel_position_t, north->pixels[pixel_position_t] );
	//printf("piel_position[%d]: %d\n", pixel_position_t + 1, north->pixels[pixel_position_t + 1] );
		pixel_color = &((north->pixels)[pixel_position_t * sizeof(uint32_t)]);
	}*/
	
	return (pixel_color);
}

uint8_t	*get_pixel_south(mlx_texture_t *south, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)south->width / point->h) * y;
	y_pixel_t = ((int)point->x % MINI);
	pixel_position_t = ((int)x_pixel_t * south->width + (int)y_pixel_t);
	pixel_color = &((south->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_east(mlx_texture_t *east, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)east->height / point->h) * y;
	y_pixel_t = ((int)point->y % MINI);
	pixel_position_t = ((int)x_pixel_t * east->width + (int)y_pixel_t);
	pixel_color = &((east->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_west(mlx_texture_t *west, t_point *point, double y)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)west->height / point->h) * y;
	y_pixel_t = ((int)point->y % MINI);
	pixel_position_t = ((int)x_pixel_t * west->width + (int)y_pixel_t);
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
		pixel = get_pixel_north(img->north_texture, point, y);
	else if (point->face == 'S')
		pixel = get_pixel_south(img->south_texture, point, y);
	else if (point->face == 'E')
		pixel =get_pixel_east(img->east_texture, point, y);
	else if (point->face == 'W')
		pixel = get_pixel_west(img->west_texture, point, y);
	r = *(pixel++);
	g = *(pixel++);
	b = *(pixel++);
	return (get_rgba(r, g, b, 255));
}
