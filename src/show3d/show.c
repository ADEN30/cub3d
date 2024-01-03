#include "../../include/cub3d.h"

static double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void	draw_all(t_vars *vars, double height, int i, int x)
{
	int	y;

	y = -1;
	while (++y < vars->mlx->height - 1)
    {
        if (y < vars->mlx->height / 2 - (height / 2))
			mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(100, 150, 255, 255));
        if (y >= (vars->mlx->height / 2 - (height / 2))
            && y < (vars->mlx->height / 2 + (height / 2)))
			mlx_put_pixel(vars->style->images->threed, x, y, get_pixel(vars, height, y, i));
        if (y >= vars->mlx->height / 2 + (height / 2))
			mlx_put_pixel(vars->style->images->threed, x, y, get_rgba(191, 170, 143, 255));
	}
}

static double   calc_height(t_vars *vars, int i)
{
    double  d_wall;
    double  w_height;
	double	ofsangle;

    d_wall = distance(vars->pers->x, vars->pers->y,
        vars->pers->rays[0]->points[i].x, vars->pers->rays[0]->points[i].y);
	ofsangle = vars->pers->angle - vars->pers->rays[0]->points[i].angle;
	d_wall = d_wall * cos(ofsangle);
    w_height = 600 / (d_wall * 0.1);
    return (w_height);
}

void	show_view(t_vars *vars)
{
	int		i;
	int		x;
	double	height;
	
	i = 799;
	x = 0;
	if (vars->style->images->threed)
        mlx_delete_image(vars->mlx, vars->style->images->threed);
    vars->style->images->threed = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	while (i >= 0)
	{
		height = calc_height(vars, i);
		draw_all(vars, height, i, x);
		i--;
		x++;
	}
    mlx_image_to_window(vars->mlx, vars->style->images->threed, 0, 0);
	//show_minimap(vars);
}
