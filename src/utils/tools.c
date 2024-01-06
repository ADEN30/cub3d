/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:45:32 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/05 17:45:46 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	check_line(char *line)
{
	line[ft_strlen(line) - 1] = 0;
	while (*line == ' ')
		line++;
	while (*line)
	{
		if (ft_isdigit(*line) || (*line == ',' && ft_isdigit(*(line + 1))))
			line++;
		else
			return (1);
	}
	return (0);
}

uint32_t	value_rgb(char *line, t_vars *vars)
{
	int	value;

	value = ft_atoi(line);
	if (value > 255)
	{
		print_error("Incorrect color values\n");
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
