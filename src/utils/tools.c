/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:10:12 by eberger           #+#    #+#             */
/*   Updated: 2023/08/03 14:16:57 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	value_rgb(char *line)
{
	int	value;

	value = ft_atoi(line);
	return ((uint32_t)value);
}

char	find_case(t_list *list, int x, int y)
{
	char	*chr;

	while (y-- && list)
		list = list->next;
	if (!list)
		return (0);
	chr = list->content;
	return (chr[x]);
}

int	put_pixels(mlx_image_t *img, uint32_t color)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
	return (0);
}

int	largest_line(t_list *list)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = list;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->content) > len)
			len = ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	return (len);
}
