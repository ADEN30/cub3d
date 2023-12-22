#include "../../include/cub3d.h"

int	check_line(char *line)
{
	line[ft_strlen(line) - 1] = 0;
	while (*line == ' ')
		line++;
	while (*line)
	{
		if (ft_isdigit(*line) || (*line == ',' && ft_isdigit(*(line + 1))))
			line++;
		else
			return (1);
	}
	return (0);
}

uint32_t	value_rgb(char *line, t_vars *vars)
{
	int	value;

	value = ft_atoi(line);
	if (value > 255)
	{
		print_error("Incorrect color values\n");
		free_vars(vars);
		exit(1);
	}
	return (value);
}

char	find_case(t_list *list, int x, int y)
{
	char	*chr;

	while (y-- && list)
		list = list->next;
	if (!list)
		return (0);
	chr = list->content;
	return (chr[x]);
}

int	put_pixels(mlx_image_t *img, uint32_t color)
{
	unsigned int	x;
	unsigned int	y;

	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->height)
			mlx_put_pixel(img, x, y, color);
	}
	return (0);
}

int	largest_line(t_list *list)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = list;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->content) > len)
			len = ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	return (len);
}
