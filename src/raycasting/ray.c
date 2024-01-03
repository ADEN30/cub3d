/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:32:08 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/03 19:25:08 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

char    change_xy(double *x, double *y, double *xy, char face)
{
    *y = xy[1];
    *x = xy[0];
    return (face);
}

void    define_angle(t_vars * vars)
{
    if (vars->pers->angle < 0)
        vars->pers->angle =  2 * M_PI + vars->pers->angle;
    if (vars->pers->angle > 2 * M_PI)
        vars->pers->angle = vars->pers->angle - 2 * M_PI;
}

char    check_move(t_vars *vars, double *x, double *y, int i)
{
    double  h[2];
    double  dst[2];
    double  v[2];
    char    face[2];
    double  ra;

	h[0] = v[0] = *x;
	h[1] = v[1] = *y;
    ra = vars->pers->angle;
    vars->pers->angle = vars->pers->angle + (1 * M_PI / 180) * 30;
    define_angle(vars);
    horizontal_intersection(vars, h, face);
    dst[0] = dist(vars, h[0], h[1]);
    vertical_intersection(vars, v, face);
    dst[1] = dist(vars, v[0], v[1]);
    vars->pers->rays[0]->points[i].angle = vars->pers->angle;
    vars->pers->angle = ra;
    if ((dst[0] <= dst[1] && dst[0] != 0) || dst[1] == 0)
        return (change_xy(x, y, h, face[1]));
    else if ((dst[1] < dst[0] && dst[1] != 0) || dst[0] == 0)
        return (change_xy(x, y, v, face[0]));
    return ('0');
}

void	find_wall(t_vars* vars)
{
	double		x;
	double		y;
	int			i;

	i = 799;
	vars->pers->rays[0]->points = ft_calloc(sizeof(t_point), 800);
	vars->map->face = ft_calloc(sizeof(char), (800 + 1));
    if (!vars->pers->rays[0]->points || !vars->map->face)
    {
		print_error("Error while printing rays on minimap\n");
		free_vars(vars);
		exit(1);
    }
	while (i >= 0)
	{
        y = vars->pers->y;
        x = vars->pers->x;
        vars->map->face[i] = check_move(vars, &x, &y, i);
        vars->pers->rays[0]->points[i].y = y;
        vars->pers->rays[0]->points[i].x = x;
        i--;
        vars->pers->angle -= 0.075 * M_PI / 180;
	}
    vars->pers->angle = vars->pers->angle + (60 * M_PI / 180);
    printf("angle = %f\n", vars->pers->angle * 180 / M_PI);
    printf("x = %f\n", vars->pers->x);
    printf("y = %f\n", vars->pers->y);
    printf("delta x = %f\n", vars->pers->deltax);
    printf("delta y = %f\n", vars->pers->deltay);
    printf("\n");
}
