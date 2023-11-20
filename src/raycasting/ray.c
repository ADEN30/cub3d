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
	//printf("angle 1: %.2f\n", vars->pers->rays[0]->angle);
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
		if ((x >= wall->instances[i].x && x <= wall->instances[i].x + wall->width && y >= wall->instances[i].y && y <= wall->instances[i].y + wall->height))
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
	printf("%d\n", vars->pers->rays[0]->count_points);
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

			w += 1;
			y = round(a*(w - vars->pers->x)) + vars->pers->y;
		}	
		if (pixels && &pixels[i])
		{
			pixels[i].x = w - 1;
			pixels[i].y = round(a*(pixels[i].x - vars->pers->x)) + vars->pers->y;
			pixels[i].coeff = a;
			pixels[i].dir = 0;
			i++;
		//	printf("%f\n", pixels[i].coeff);
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

void	completion_plan(t_vars* vars)
{
	//double	old_a;
	t_point*	pixel;
	int		i;
	double		x;
	double		y;

	i = 0;
	pixel = vars->pers->rays[0]->points;
	mlx_delete_image(vars->mlx, vars->pers->rays[0]->img);
	vars->pers->rays[0]->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	while (i < vars->pers->rays[0]->count_points)
	{	
		x = vars->pers->x;
		y = pixel[i].coeff * (x);
		while (!test_wall(vars, round(x), round(y)) && round(x) < vars->mlx->width && round(y) < vars->mlx->height)
		{
			
			//printf("x[%d]: %f\n", i, x);
			mlx_put_pixel(vars->pers->rays[0]->img, round(x), round(y),  get_rgba(255, 0, 0, 255));
			x += 1;
			y = pixel[i].coeff * (x);	
		}
		i++;
	}
	
}

/*void	change_plan(t_vars* vars)
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
		x = (pixel[i].x - vars->pers->x) * cos(0.523599) + (pixel[i].y - vars->pers->y) * sin(0.523599) + vars->pers->x;
		
		y = -(pixel[i].x - vars->pers->x) * sin(0.523599) + (pixel[i].y - vars->pers->y) * cos(0.523599) + vars->pers->y;
		if (!test_wall(vars, round(x), round(y)) && x < vars->mlx->width && y < vars->mlx->height)	
			mlx_put_pixel(vars->pers->rays[0]->img, round(x), round(y),  get_rgba(255, 0, 0, 255));
		pixel[i].x = x;
		pixel[i].y = y;
		pixel[i].coeff = (y) / (x);	
		//printf("a[%d]: %.2f\t x= %f\t", i, pixel[i].coeff, pixel[i].x);
		//printf("y[%d]: %f\t y'[%d]: %f\n", i, y, i, pixel[i].coeff * x);
		i++;
	}
	vars->pers->rays[0]->points = pixel;
	printf("x[pers]: %d y[pers]: %d\n", vars->pers->x, vars->pers->y);
//	completion_plan(vars);
}*/

t_point	calc_rot(double x, double y, t_vars* vars)
{
	t_point pixel;

	pixel.x = (x - vars->pers->x) * cos(0.0174533) + (y - vars->pers->y) * sin(0.0174533) + vars->pers->x;
	pixel.y = -(x - vars->pers->x) * sin(0.0174533) + (y - vars->pers->y) * cos(0.0174533) + vars->pers->y;
	return (pixel);
}

void	change_plan(t_vars* vars)
{
	int	i;
	t_point*	pixel;
	double		x;
	double		y;
	double		a;

	mlx_image_to_window(vars->mlx, vars->pers->rays[0]->img, 0, 0);
	pixel = vars->pers->rays[0]->points;
	i = 0;

	while (i < vars->pers->rays[0]->count_points)
	{
		/*x = (pixel[i].x - vars->pers->x) * cos(0.0174533) + (pixel[i].y - vars->pers->y) * sin(0.0174533) + vars->pers->x;
		y = -(pixel[i].x - vars->pers->x) * sin(0.0174533) + (pixel[i].y - vars->pers->y) * cos(0.0174533) + vars->pers->y;*/
		//printf("x: %f y: %f\n", pixel[i].x, pixel[i].y);
		pixel[i] = calc_rot(pixel[i].x, pixel[i].y, vars);
		//printf("x: %f y: %f\n", pixel[i].x, pixel[i].y);
		a = (pixel[i].y - vars->pers->y ) / (pixel[i].x - vars->pers->x);
		printf("a: %f\n", a);
		x = vars->pers->x;
		y = ceil(a * (x - vars->pers->x) + vars->pers->y);
		if (a >= 0)
		{
			while (!test_wall(vars, x, y) && a > 0 && x > 0 && x < vars->mlx->width && y > 0 && y < vars->mlx->height)
			{
				//printf("x[%d]: %f y[%d]: %f\n", i, round(x), i, round(y));
				mlx_put_pixel(vars->pers->rays[0]->img, x, y,  get_rgba(255, 0, 0, 255));
				x += 1;
				y = ceil(a * (x - vars->pers->x) + vars->pers->y);
			}
		}
		else if (a < 0)
		{
			while (!test_wall(vars, x, y) && a < 0 && x < vars->mlx->width && y > 0 && y < vars->mlx->height)
			{
				//printf("x[%d]: %f y[%d]: %f\n", i, round(x), i, round(y));
				mlx_put_pixel(vars->pers->rays[0]->img, x, y,  get_rgba(245, 40, 145, 255));
				x += 1;
				y = round(a * (x - vars->pers->x) + vars->pers->y);
			}
		}
		i++;	
	}
	printf("x[pers]: %d y[pers]: %d\n", vars->pers->x, vars->pers->y);
	printf("x: %f, y: %f\n", x, y);
	printf("mlx width: %d height: %d\n", vars->mlx->width, vars->mlx->height);
	printf("count_points: %d/t i: %d\n", vars->pers->rays[0]->count_points, i);
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
			mlx_put_pixel(vars->pers->rays[0]->img, w, y,  get_rgba(255, 0, 0, 255));
			w += 1;
			y = round(a*(w - vars->pers->x)) + vars->pers->y;
		}
		vars->pers->rays[0]->count_points++;
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
