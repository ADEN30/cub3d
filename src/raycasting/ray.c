#include "../../include/cub3d.h"

int	find_length(int x, int y, t_pers *pers)
{
	int	a;
	int	b;
	int	c;

	a = pow(pers->x - x, 2);
	b = pow(pers->y - y, 2);
	c = sqrt(a + b);
	return (c);
}

int	init_points(int length, t_ray *ray)
{
	int	i;

	i = 0;
	if (ray->count_points < length)
	{
		if (ray->count_points != 0)
			free(ray->points);
		ray->points = malloc(sizeof(t_point) * length);
		if (!ray->points)
			return (1);
		ray->count_points = length;
		while (i < length)
		{
			ray->points[i].x = 0;
			ray->points[i].y = 0;
			ray->points[i].enabled = 0;
			i++;
		}
	}
	return (0);
}

int	calc_line(int x1, int y1, int id_ray, t_vars *vars)
{
	t_ray	**rays;
	t_pers	*pers;
	int		i;

	i = 0;
	pers = vars->pers;
	rays = pers->rays;
	double	angle_rad = rays[id_ray]->dir * M_PI / 180.0;
	double dx = pers->ray_length * cos(angle_rad);
	double dy = pers->ray_length * sin(angle_rad);

	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	if (init_points(steps, rays[id_ray]))
		return (1);

	double xIncrement = dx / steps;
	double yIncrement = dy / steps;

	double x = x1;
	double y = y1;

	i = 0;
	while (i <= steps && find_case(vars->map->lines, x / DIMENSION, y / DIMENSION) != '1')
	{
		rays[id_ray]->points[i].x = round(x);
		rays[id_ray]->points[i].y = round(y);
		rays[id_ray]->points[i].enabled = 1;
		x += xIncrement * (i / 50 + 1);
		y += yIncrement * (i / 50 + 1);
		i++;
	}
	rays[id_ray]->length = find_length(round(x - xIncrement), round(y - yIncrement), pers);
	rays[id_ray]->col_x = round(x - xIncrement);
	rays[id_ray]->col_y = round(y - yIncrement);
	rays[id_ray]->distance_proj = rays[id_ray]->length * cos(rays[id_ray]->dir);
	while (i < rays[id_ray]->count_points)
	{
		rays[id_ray]->points[i].enabled = 0;
		i++;
	}
	return (0);
}


//A supprimer
int	draw_line(int x1, int y1, int id_ray, t_vars *vars)
{
	t_ray	**rays;
	t_pers	*pers;
	int		i;

	i = 0;
	pers = vars->pers;
	rays = pers->rays;
	double	angle_rad = rays[id_ray]->dir * M_PI / 180.0;
	double dx = pers->ray_length * cos(angle_rad);
	double dy = pers->ray_length * sin(angle_rad);

	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	double xIncrement = dx / steps;
	double yIncrement = dy / steps;

	double x = x1;
	double y = y1;

	uint32_t color = get_rgba(255, 0, 0, 255);
	i = 0;
	while (i <= steps && find_case(vars->map->lines, x / DIMENSION, y / DIMENSION) != '1')
	{
		if (rays[id_ray]->img->count < (unsigned long)steps)
		{
			if (mlx_image_to_window(vars->mlx, rays[id_ray]->img, round(x), round(y)) == -1)
				return (printf("error\n"), 1);
			if (put_pixels(rays[id_ray]->img, color))
				return (printf("error\n"), 1);
		}
		else
		{
			rays[id_ray]->img->instances[i].x = round(x);
			rays[id_ray]->img->instances[i].y = round(y);
			rays[id_ray]->img->instances[i].enabled = 1;
		}
		x += xIncrement;
		y += yIncrement;
		i++;
	}
	while (i < (int)rays[id_ray]->img->count)
	{
		rays[id_ray]->img->instances[i].enabled = 0;
		i++;
	}
	return (0);
}

/*  void	ft_raycasting(void *param)
{
	t_vars	*vars;
	t_pers	*pers;
	int		i;

	vars = param;
	pers = vars->pers;
	i = 0;
	while (pers->rays[i])
	{
		pers->rays[i]->dir = pers->orientation + (i * 60 / 1080) - 30;
		if (MAP == 1)
			draw_line(pers->x, pers->y, i, vars);
		calc_line(pers->x, pers->y, i, vars);
		i++;
	}
}*/

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
	printf("ok\n");
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
		/*  if (pixels && &pixels[i])
		{
			pixels[i].coeff = a;
			printf("%f\n", pixels[i].coeff);
		}*/
		vars->pers->rays[0]->coefdir += 0.003;
	}
	vars->pers->rays[0]->coefdir = 0.00;
	vars->pers->rays[0]->angle = 0.00;
	vars->pers->rays[0]->d1 = 0.00;
	vars->pers->rays[0]->d2 = 0.00;
	vars->pers->rays[0]->d3 = 0.00;
	vars->pers->rays[0]->points = pixels;
}

void	change_plan(t_vars* vars)
{
	int	i;
	t_point*	pixel;

	i = 0;
	pixel = vars->pers->rays[0]->points;
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	while (pixel && i < vars->pers->rays[0]->count_points - 1)
	{
		if (pixel[i].x == vars->pers->x && pixel[i].y == vars->pers->y)
			printf("x1: %d y1: %d\n", pixel[i].x, pixel[i].y);
		pixel[i].x = round((pixel[i].x)  * cosh(M_PI/180) - (pixel[i].y ) * sinh(M_PI/180));
		pixel[i].y = round((pixel[i].x - vars->pers->x) * sinh(M_PI/180) + (pixel[i].y)* cosh(M_PI/180));
		if (!test_wall(vars, pixel[i].x, pixel[i].y) && pixel[i].x < vars->mlx->width && pixel[i].y < vars->mlx->height)
			mlx_put_pixel(vars->pers->rays[0]->img, pixel[i].x, pixel[i].y,  get_rgba(255, 0, 0, 255));
		if (pixel[i].x == 0 && pixel[i].y == 0)
			printf("x2: %d y2: %d\n", pixel[i].x, pixel[i].y);
		i++;
	}

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
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	vars->pers->rays[0]->coefdir = 0.00;
	while (calc_angle(vars) <= 60 && !test_wall(vars, vars->pers->x, vars->pers->y))
	{
 		a = vars->pers->rays[0]->coefdir;
		w = vars->pers->x;
		y = round(a*(w - vars->pers->x)) + vars->pers->y;
		while (!test_wall(vars, w, y) && w < vars->mlx->width && y < vars->mlx->height)
		{
				mlx_put_pixel(vars->pers->rays[0]->img, w, y,  get_rgba(255, 0, 0, 255));
			vars->pers->rays[0]->count_points++;
			w += 1;
			y = round(a*(w - vars->pers->x)) + vars->pers->y;
		}
		vars->pers->rays[0]->coefdir += 0.003;
	}
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
