/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:05:36 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/27 22:11:40 by agallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void    wall_column(t_vars *vars, int x, double w_height, int i)
{
    int     j;

    j = -1;
    while (++j < vars->mlx->height)
    {
        if (j > (vars->mlx->height / 2 - (w_height / 2))
            && j < (vars->mlx->height / 2 + (w_height / 2)))
        {
            if (vars->pers->rays[0]->points[i].dir == 2)
				mlx_put_pixel(vars->style->images->threed, x, j, get_rgba(103, 52, 71, 255));
            else if (vars->pers->rays[0]->points[i].dir == 1)
				mlx_put_pixel(vars->style->images->threed, x, j, get_rgba(163, 159, 146, 255));
            else if (vars->pers->rays[0]->points[i].dir == 3)
				mlx_put_pixel(vars->style->images->threed, x, j, get_rgba(255, 255, 255, 255));
            else if (vars->pers->rays[0]->points[i].dir == 4)
 				mlx_put_pixel(vars->style->images->threed, x, j, get_rgba(0, 0, 0, 255));
        }
        else if (vars->pers->rays[0]->points[i].dir == 5)
                mlx_put_pixel(vars->style->images->threed, x, j,
                 get_rgba(0, 0, 0, 255));
    }
}

static double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

static double   calculate_height(t_vars *vars, int i)
{
    double  d_wall;
    double  w_height;

    d_wall = distance(vars->pers->x, vars->pers->y,
        vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
    w_height = 1500 / (d_wall * 0.03);
    //printf("percu = %f\n", w_height);
    //usleep(100000);
    return (w_height);
}

static int  calculate_rays(t_vars *vars)
{
    double     nb_rays;

	nb_rays = 0.0000;
    nb_rays = define_wall(vars);
	printf("width : %d nb_rays: %f count ::::: %f\n", vars->mlx->width, nb_rays, (vars->mlx->width / nb_rays) + 1);
    if (vars->mlx->width % (int)nb_rays  != 0)
        return ((vars->mlx->width / nb_rays) + 1);
    else
        return (vars->mlx->width / nb_rays);
}

void    show_vue(t_vars *vars)
{
    int     i;
    int     j;
    int     x;
    int     count;

    i = vars->mlx->width;
    x = 0;
    count = calculate_rays(vars);
	//vars->mlx = mlx_init(1500, 1500, "cub3d", true);
    if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
    while (x < vars->mlx->width)
    {
        if (vars->pers->rays[0]->points[i].dir != 0)
        {
            //printf("x = %d | dir = %d\n", x, vars->pers->rays[0]->points[i].dir);
            j = -1;
            while (++j < count)
                wall_column(vars, x + j, calculate_height(vars, i), i);
            x = x + j;
        }
        i--;
    }
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
    vars->style->images->threed->instances[0].z = 1;
}


int	search_tab(t_point pixel, t_point* map, int size, t_vars* vars)
{
	int	i;
	int	width;
	int	height;
	
	i = 0;
	width = vars->style->images->wall_image->width;
	height = vars->style->images->wall_image->height;
	while (i < size)
	{
		if (pixel.x >= map[i].x && pixel.x <= map[i].x + width && pixel.y >= map[i].y && pixel.y <= map[i].y + height)
		return (1);
		i++;
	}	
	return (0);
}

char	found_wall(t_vars* vars, int i)
{
	t_point* pixel;

	pixel = vars->pers->rays[0]->points;
	if (pixel[i].x >= vars->pers->x)
	{
		if (search_tab(pixel[i], vars->map->E, vars->map->est, vars))
		return ('e');
		if (pixel[i].y >= vars->pers->y)
		{	
			if (search_tab(pixel[i], vars->map->S, vars->map->sud, vars))
		return ('s');
		}
		else
		{
			if (search_tab(pixel[i], vars->map->N, vars->map->nord, vars))
		return ('n');

		}
	}
	else
	{
		if (search_tab(pixel[i], vars->map->O, vars->map->ouest, vars))
		return ('o');
		if (pixel[i].y >= vars->pers->y)
		{	
			if (search_tab(pixel[i], vars->map->S, vars->map->sud, vars))
		return ('s');
		}
		else
		{
			if (search_tab(pixel[i], vars->map->N, vars->map->nord, vars))
		return ('n');

		}
	}
	return ('z');
}

void select_color(char c, t_vars* vars, int x, int y)
{
	if (c == 'e')
		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(103, 52, 71, 255));
	else if (c == 'o')
 		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(163, 159, 146, 255));
	else if (c == 's')
 		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(0, 0, 0, 255));
	else if (c == 'n')
		mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(255, 255, 255, 255));
}

void	draw_height(t_vars* vars, double height, int x, char c)
{
	int	y;
	int start;
	
	start = (vars->mlx->width - height) / 2;
	y = start;
	while (y < height + start)
	{
		select_color(c, vars, x, y);
		y++;
	}
}

void	create_vue(t_vars* vars)
{
	int	x;
	int	i;
	double	height;
	char	c;
	
	x = 0;
	i = 0;
	if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
	while (x < vars->mlx->width)
	{
		while (i < vars->pers->rays[0]->length)
		{
			height = calculate_height(vars, i);
			printf("height: %f\n", height);
			c = found_wall(vars, i);
			printf("c: %c\n", c);
			draw_height(vars, height, x, c);
			i++;
			break ;
		}
		x++;
	}
	printf("ok\n");
}
