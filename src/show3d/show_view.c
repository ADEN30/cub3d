/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:47:45 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/06 17:07:58 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_point	*get_point(t_vars *vars, int i)
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
	while (++y < vars->mlx->height - 1)
	{
		if (y < vars->mlx->height / 2 - (point->h / 2))
			mlx_put_pixel(vars->style->images->threed, i, y,
				vars->style->roof);
		if (y >= (vars->mlx->height / 2 - (point->h / 2))
			&& y < (vars->mlx->height / 2 + (point->h / 2)))
			mlx_put_pixel(vars->style->images->threed, i, y,
				get_pixel(vars, point, y));
		if (y >= vars->mlx->height / 2 + (point->h / 2))
			mlx_put_pixel(vars->style->images->threed, i, y,
				vars->style->floor);
	}
	free(point);
}

static void	calc_height(t_vars *vars, int x)
{
	double	ofsangle;

	ofsangle = vars->pers->angle - vars->pers->points[x].angle;
	vars->pers->points[x].dst = vars->pers->points[x].dst
		* cos(ofsangle);
	vars->pers->points[x].h = vars->mlx->height
		/ (vars->pers->points[x].dst * 0.3);
}

void	show_view(t_vars *vars)
{
	int		i;
	int32_t	cs;

	i = 0;
	while (i <= 799)
	{
		calc_height(vars, i);
		draw_all(vars, i);
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
