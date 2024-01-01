#include "../../include/cub3d.h"

void	clear_pixel2(t_ray **ray)
{
	ray[0]->img->instances[ray[0]->img->count - 1].enabled = 0;
}
