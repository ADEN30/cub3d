/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 07:47:05 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/30 14:53:31 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint8_t	*get_pixel_east(t_vars *vars, double height, double x, int y, int i)
{
	double		xi;
	double		yi;
	int			pos;
	uint8_t		*px_ind;

	(void)y;
	printf("x = %f\n", x);
	printf("y = %d\n", y);
	//i = ((double)(vars->style->images->east_texture->height % 32) / height) * x;
	//j = y / height * (1500 / );
	xi = vars->pers->rays[0]->points[i].x / 32 * vars->mlx->width;
	yi = 0; 
	printf("i = %f j = %f\n", xi, yi);
	sleep(2);
	px_ind = 0;
	pos = (yi * vars->mlx->width + xi) * 3;
	px_ind = &((vars->style->images->east_texture->pixels)[pos * sizeof(uint32_t)]);
	return (px_ind);
}

uint32_t	get_pixel(t_vars *vars, int height, int x, int y, int i)
{
	//int		r;
	//int		g;
	//int		b;
	uint8_t	*pixel;

	//y = vars->mlx->height - (height / 2);
		pixel = get_pixel_east(vars, height, x, y, i);
	//r = *(pixel++);
	//g = *(pixel++);
	//b = *(pixel++);
	(void)i;
	(void)y;
	(void)height;
	(void)x;
	//if (vars->pers->rays[0]->points[i].dir == 'n')
		//return (get_rgba(100, 100, 100, 255));
	//else if (vars->pers->rays[0]->points[i].dir == 's')
		//return (get_rgba(255, 0, 0, 255));
	//else if (vars->pers->rays[0]->points[i].dir == 'e')
		//return (get_rgba(0, 255, 0, 255));
	//else if (vars->pers->rays[0]->points[i].dir == 'o')
		//return (get_rgba(0, 0, 255, 255));
	//return (get_rgba(0, 0, 0, 255));
	return (pixel);
}
