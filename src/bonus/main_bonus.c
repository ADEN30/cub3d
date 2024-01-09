/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:46 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/08 22:01:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//void	print_array(t_vars *vars)
//{
	//mlx_image_t	*image;

	//image = mlx_new_image(vars->mlx, vars->style->images->west_texture->width,
		//vars->style->images->west_texture->height);
	//printf("width: %d\n", vars->style->images->west_texture->width);
	//printf("height: %d\n", vars->style->images->west_texture->height);
	//printf("pixels: %d\n", vars->style->images->west_texture->bytes_per_pixel);
	//int width = vars->style->images->west_texture->width;
	//int height = vars->style->images->west_texture->height;
	//int bpp = 4; // bits per pixel convertis en bytes per pixel
	//int size_line = 512; // nombre d'octets par ligne de l'image

	//for (int y = 0; y < height; y++)
	//{
		//for (int x = 0; x < width; x++)
		//{
			//uint32_t pixel[4];
			//int pixel_index = y * size_line + x * bpp;
			//printf("pixel_index: %d\n", pixel_index);
			//pixel[0] = vars->style->images->west_texture->pixels[pixel_index];
			//pixel[1] = vars->style->images->west_texture->pixels[pixel_index + 1];
			//pixel[2] = vars->style->images->west_texture->pixels[pixel_index + 2];
			//pixel[3] = bpp == 4 ? vars->style->images->east_texture->pixels[pixel_index + 3] : 0xff;
			//uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
			//printf("color: %d\n", pixel[0]);
			//printf("color: %d\n", pixel[1]);
			//printf("color: %d\n", pixel[2]);
			//printf("color: %d\n", pixel[3]);
			//mlx_put_pixel(image, x, y, color);
		//}
	//}
	//mlx_image_to_window(vars->mlx, image, 0, 128);
//}

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars || parse_map(argc, argv, vars))
		return (free_vars(vars), 1);
	vars->mlx = mlx_init(1280, 720, "cub3d", true);
	if (!vars->mlx)
		return (free_vars(vars), 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (init_graphic(vars))
		return (free_vars(vars), 1);
	if (show_minimap(vars))
		return (free_vars(vars), 1);
	//print_array(vars);
	find_wall(vars);
	rays_on_minimap(vars);
	show_view(vars);
	//mlx_mouse_hook(vars->mlx, mouse, vars);
	mlx_loop_hook(vars->mlx, move, vars);
	mlx_loop(vars->mlx);
	return (free_vars(vars), 0);
}
