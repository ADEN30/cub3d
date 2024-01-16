/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:45:32 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/16 10:46:07 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	line_isprint(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isprint(line[i]))
			return (0);
		i++;
	}
	return (1);
}

uint32_t	value_rgb(char *line, t_vars *vars)
{
	int	value;

	value = ft_atoi(line);
	if (value > 255)
	{
		print_error("Incorrect color values");
		free_vars(vars);
		exit(1);
	}
	return (value);
}

int	put_pixels(mlx_image_t *img, uint32_t color)
{
	unsigned int	x;
	unsigned int	y;

	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
			mlx_put_pixel(img, x, y, color);
	}
	return (0);
}
