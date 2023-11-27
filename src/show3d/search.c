
#include "../../include/cub3d.h"

static int	check_nb(int i, int j)
{
	//printf("i= %d j= %d\n", i, j);
	return (abs(i - j));
}

int ft_search(t_vars *v)
{
    int i;
    int j;
	int count;

	i = 0;
	j = 1;
	count = 0;
    while (i < v->pers->rays[0]->length)
	{
		//printf("%d %d\n", (int)v->pers->rays[0]->points[i].x, (int)v->pers->rays[0]->points[i].y);
		j = i + 1;
		while (v->pers->rays[0]->points[j].x == 0 && v->pers->rays[0]->points[j].x == 0)
			j++;
		if ((int)v->pers->rays[0]->points[i].x == (int)v->pers->rays[0]->points[j].x)
			count += check_nb(v->pers->rays[0]->points[i].y, v->pers->rays[0]->points[j].y);
		else if ((int)v->pers->rays[0]->points[i].y == (int)v->pers->rays[0]->points[j].y)
			count += check_nb(v->pers->rays[0]->points[i].x, v->pers->rays[0]->points[j].x);
		i = j;
	}
	return (count);
}
