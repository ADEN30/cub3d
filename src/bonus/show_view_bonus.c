/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_view_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:47:45 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/08 21:36:19 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_point	*get_point(t_vars *vars, int i)
{
	t_point	*point;

	point = ft_calloc(sizeof(t_point), 1);
	if (point == NULL)
		return (NULL);
	point->x = vars->pers->points[i].x;
	point->y = vars->pers->points[i].y;
	point->dst = vars->pers->points[i].dst;
	point->h = vars->pers->points[i].h;
	point->angle = vars->pers->points[i].angle;
	point->face = vars->pers->points[i].face;
	return (point);
}

void	draw_all(t_vars *vars, int i)
{
	t_point	*point;
	int		y;

	y = -1;
	point = get_point(vars, i);
	while (++y < MAX_HEIGHT)
	{
		if (y >= (MAX_HEIGHT / 2 - (point->h / 2))
			&& y < (MAX_HEIGHT / 2 + (point->h / 2)))
		{
			//printf("y %d\n", y);
			mlx_put_pixel(vars->style->images->threed, i, y,
				get_pixel(vars, point, y));
			point->test += 128;
		}
		else if (y < MAX_HEIGHT / 2 - (point->h / 2))
			mlx_put_pixel(vars->style->images->threed, i, y,
				vars->style->roof);
	
		if (y >= MAX_HEIGHT / 2 + (point->h / 2))
			mlx_put_pixel(vars->style->images->threed, i, y,
				vars->style->floor);
	}

	free(point);
}

static void	calc_height(t_vars *vars, int i)
{
	double	ofsangle;

	ofsangle = vars->pers->angle - vars->pers->points[i].angle;
	vars->pers->points[i].dst = vars->pers->points[i].dst
		* cos(ofsangle);
	printf("dst: %f\n", vars->pers->points[i].dst);
	vars->pers->points[i].h = (MAX_HEIGHT / (vars->pers->points[i].dst * 0.25));
}

void	show_view(t_vars *vars)
{
	int		i;
	int32_t	cs;

	i = 0;
	
	while (i < MAX_WIDTH)
	{
		calc_height(vars, i);
		draw_all(vars, i);
		vars->pers->points->test = 0;
		printf("point->h %f\n", vars->pers->points[i].h);
		i++;
	}
	cs = mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
	if (cs == -1)
	{
		print_error("Error : Map can not be generated\n");
		free_vars(vars);
		exit(1);
	}
	vars->style->images->threed->instances->z = 0;
}
