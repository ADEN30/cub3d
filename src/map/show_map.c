#include "../../include/cub3d.h"

int	print_case(int *loc, t_vars *vars, mlx_image_t **img, uint32_t color)
{
	if (!*img)
	{
		*img = mlx_new_image(vars->mlx, DIMENSION, DIMENSION);
		if (!*img)
			return (1);
	}
	if (mlx_image_to_window(vars->mlx, *img, loc[1] * (*img)->width, loc[0]
		* (*img)->height) == -1)
		return (1);
	//mlx_set_instance_depth((*img)->instances, 1);
	if (put_pixels(*img, color))
		return (1);
	return (0);
}

int	which_case(char c, int *loc, t_vars *vars)
{
	t_images	*images;

	images = vars->style->images;
	if (c == '1' && MAP == 1)
		print_case(loc, vars, &(images->wall_image), vars->style->wall);
	else if (ft_strchr("NSWE", c))
		vars->pers = init_pers(loc[1] * DIMENSION + DIMENSION / 2,
		loc[0] * DIMENSION + DIMENSION / 2,
		find_case(vars->map->lines, loc[1], loc[0]), vars);
	else
		return (1);
	return (0);
}

int	show_map(t_vars *vars)
{
	int		loc[2];
	char	c;

	loc[0] = 0;
	while (find_case(vars->map->lines, 0, loc[0]))
	{
		loc[1] = 0;
		c = find_case(vars->map->lines, loc[1], loc[0]);
		while (find_case(vars->map->lines, loc[1], loc[0]))
		{
			if (which_case(c, loc, vars))
				return (printf("Error print case\n"), 1);
			loc[1]++;
			c = find_case(vars->map->lines, loc[1], loc[0]);
		}
		loc[0]++;
	}
	return (0);
}
