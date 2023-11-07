#include "../../include/cub3d.h"



double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}


double	calc_angle(t_vars* vars)
{
	double	d1;
	double	d2;
	double	d3;

	d1 = vars->pers->rays[0]->d1;
	d2 = vars->pers->rays[0]->d2;
	d3 = vars->pers->rays[0]->d3;
	printf("angle 1: %.2f\n", vars->pers->rays[0]->angle);
	if (!d1 && !d3)
		return (0);
	vars->pers->rays[0]->angle = round((asin(d3 / d2) / M_PI) * 180);
	//printf("angle2: %.2f\n", vars->pers->rays[0]->angle);
	return (vars->pers->rays[0]->angle);
}

int	test_wall(t_vars* param, double x, double y)
{
	size_t	i;
	mlx_image_t*	wall;

	i = 0;
	wall = param->style->images->wall_image;
	while (i < wall->count)
	{
		if ((x >= wall->instances[i].x && x < wall->instances[i].x + wall->width && y >= wall->instances[i].y && y < wall->instances[i].y + wall->height))
		{
			if (param->pers->rays[0]->coefdir == 0.00)
				param->pers->rays[0]->d1 = distance(x, y, param->pers->x, param->pers->y);
			param->pers->rays[0]->d2 = distance(x, y, param->pers->x, param->pers->y);
		param->pers->rays[0]->d3 = distance(x, param->pers->y, x, y);
			return (1);
		}
		i++;
	}
	return (0);

}

int	test_floor(t_vars* param, double x, double y)
{
	size_t	i;
	mlx_image_t*	floor;

	i = 0;
	floor = param->style->images->floor_image;
	while (i < floor->count)
	{
		if ((x >= floor->instances[i].x && x < floor->instances[i].x + floor->width && y >= floor->instances[i].y && y < floor->instances[i].y + floor->height))
		{
			if (param->pers->rays[0]->coefdir == 0.00)
			return (0);
		}
		i++;
	}
	return (1);

}
void	draw_orient(t_vars* vars)
{
	double	i;
	double	k;

	i = vars->pers->x;
	k = vars->pers->y;
	while (!test_wall(vars, i, k) && i < vars->mlx->width && k < vars->mlx->height)
	{
		//printf("i= %f\n", i);
		mlx_put_pixel(vars->pers->rays[0]->img, i, k,  get_rgba(0, 0, 255, 255));
		i += 1;
		k += 1;	
	}
	i = vars->pers->x;
	k = vars->pers->y;
	while (!test_wall(vars, i, k) && i > 0 && k > 0)
	{
		mlx_put_pixel(vars->pers->rays[0]->img, i, k,  get_rgba(0, 0, 255, 255));
		i -= 1;
		k -= 1;	
	}
}

void	ft_raycasting_malloc(void *param)
{
	t_vars	*vars;
	double	a;
	double	w;
	int		y;
	int		i;
	t_point*	pixels;

	vars = param;
	i = 0;
	if (vars->pers->rays[0]->points)
		free(vars->pers->rays[0]->points);
	pixels = malloc(sizeof(t_point) * (vars->pers->rays[0]->count_points));
	if (!pixels)
		return ;
	while (calc_angle(vars) <= 60 && !test_wall(vars, vars->pers->x, vars->pers->y))
	{
 		a = vars->pers->rays[0]->coefdir;
		w = vars->pers->x;
		y = round(a*(w - vars->pers->x)) + vars->pers->y;
		while (!test_wall(vars, w, y) && w < vars->mlx->width && y < vars->mlx->height)
		{
			pixels[i].x = w;
			pixels[i].y = y;
			i++;
			w += 1;
			y = round(a*(w - vars->pers->x)) + vars->pers->y;
		}
		if (pixels && &pixels[i])
		{
			pixels[i].coeff = a;
			printf("%f\n", pixels[i].coeff);
		}
		vars->pers->rays[0]->coefdir += 0.003;
	}
	vars->pers->rays[0]->coefdir = 0.00;
	vars->pers->rays[0]->angle = 0.00;
	vars->pers->rays[0]->d1 = 0.00;
	vars->pers->rays[0]->d2 = 0.00;
	vars->pers->rays[0]->d3 = 0.00;
	vars->pers->rays[0]->points = pixels;
	printf("nbr rayons: %d\n", vars->pers->rays[0]->n_rays);
}

void	change_plan(t_vars* vars)
{	
	t_point* pixel;
	int			i;
	double		x;
	double		y;

	i = 0;	
	pixel = vars->pers->rays[0]->points;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	while (i < vars->pers->rays[0]->count_points)
	{
		x = (pixel[i].x - vars->pers->x) * cos(0.087) + (pixel[i].y - vars->pers->y) * sin(0.087) + vars->pers->x;
		
		y = -(pixel[i].x - vars->pers->x) * sin(0.087) + (pixel[i].y - vars->pers->y) * cos(0.087) + vars->pers->y;
		if (!test_wall(vars, round(x), round(y)) && x < vars->mlx->width && y < vars->mlx->height)	
			mlx_put_pixel(vars->pers->rays[0]->img, round(x), round(y),  get_rgba(255, 0, 0, 255));
		pixel[i].x = x;
		pixel[i].y = y;
		i++;
	}
	vars->pers->rays[0]->points = pixel;
}

void	turn_camera(t_vars* vars)
{
	int	i;
	t_point*	pixel;
	int		old_count;


	i = 0;
	old_count = vars->pers->rays[0]->count_points;
	pixel = vars->pers->rays[0]->points;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	printf("points2: %d\n", vars->pers->rays[0]->count_points);

	while (i < old_count)
	{
		printf("a: %f\n", pixel[i].coeff);
		mlx_put_pixel(vars->pers->rays[0]->img, pixel[i].x, pixel[i].y ,  get_rgba(255, 0, 0, 255));
		i++;	
	}
}

void	ft_raycasting(void *param)
{
	t_vars	*vars;
	double	a;
	double	w;
	int		y;


	vars = param;
	vars->pers->rays[0]->count_points = 0;
	vars->pers->rays[0]->n_rays = 0;
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	while (calc_angle(vars) <= 60 && !test_wall(vars, vars->pers->x, vars->pers->y))
	{
 		a = vars->pers->rays[0]->coefdir;
		w = vars->pers->x;
		y = round(a*(w - vars->pers->x)) + vars->pers->y;
		while (!test_wall(vars, w, y) && w < vars->mlx->width && y < vars->mlx->height)
		{
			vars->pers->rays[0]->count_points++;
			mlx_put_pixel(vars->pers->rays[0]->img, w, y,  get_rgba(255, 0, 0, 255));
			w += 1;
			y = round(a*(w - vars->pers->x)) + vars->pers->y;
		}
		vars->pers->rays[0]->n_rays += 1;
		vars->pers->rays[0]->coefdir += 0.003;
	}
	vars->pers->rays[0]->a_r1 = vars->pers->rays[0]->coefdir - 0.003;
	printf("pixels: %d\n", vars->pers->rays[0]->count_points);
	vars->pers->rays[0]->coefdir = 0.00;
	vars->pers->rays[0]->angle = 0.00;
	vars->pers->rays[0]->d1 = 0.00;
	vars->pers->rays[0]->d2 = 0.00;
	vars->pers->rays[0]->d3 = 0.00;
	//draw_orient(vars);
	ft_raycasting_malloc(vars);
//	change_plan(vars);
}
