#include "../../include/cub3d.h"

uint8_t	*get_pixel_north(t_vars *vars, double w_height, double y, int i)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->north_texture->height / w_height) * y;
	y_pixel_t = (double)vars->style->images->north_texture->width / 10 * ((int)vars->pers->rays[0]->points[i].x % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->north_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->north_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_south(t_vars *vars, double w_height, double y, int i)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->south_texture->height / w_height) * y;
	y_pixel_t = (double)vars->style->images->south_texture->width / 10 * ((int)vars->pers->rays[0]->points[i].x % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->south_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->south_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_east(t_vars *vars, double w_height, double y, int i)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->east_texture->height / w_height) * y;
	y_pixel_t = (double)vars->style->images->east_texture->width / 10 * ((int)vars->pers->rays[0]->points[i].y % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->east_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->east_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint8_t	*get_pixel_west(t_vars *vars, double w_height, double y, int i)
{
	double	x_pixel_t;
	double	y_pixel_t;
	int		pixel_position_t;
	uint8_t	*pixel_color;

	x_pixel_t = ((double)vars->style->images->west_texture->height / w_height) * y;
	y_pixel_t = (double)vars->style->images->west_texture->width / 10 * ((int)vars->pers->rays[0]->points[i].y % 10);
	pixel_position_t = ((int)x_pixel_t * vars->style->images->west_texture->width + (int)y_pixel_t);
	pixel_color = &((vars->style->images->west_texture->pixels)[pixel_position_t * sizeof(uint32_t)]);
	return (pixel_color);
}

uint32_t	get_pixel(t_vars *vars, int w_height, int y, int i)
{
	int		r;
	int		g;
	int		b;
	uint8_t	*pixel;

	pixel = NULL;
	y = y - ((vars->mlx->height - w_height) / 2);
	if (y == w_height)
		y = y - 1;
	if (vars->map->face[i] == 'N')
		pixel = get_pixel_north(vars, w_height, y, i);
	else if (vars->map->face[i] == 'S')
		pixel = get_pixel_south(vars, w_height, y, i);
	else if (vars->map->face[i] == 'E')
		pixel = get_pixel_east(vars, w_height, y, i);
	else if (vars->map->face[i] == 'W')
		pixel = get_pixel_west(vars, w_height, y, i);
	r = *(pixel++);
	g = *(pixel++);
	b = *(pixel++);
	return (get_rgba(r, g, b, 255));
}