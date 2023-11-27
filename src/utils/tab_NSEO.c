/*
 * =====================================================================================
 *
 *       Filename:  tab_NSEO.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/27/23 12:55:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/cub3d.h"


int	search_EO(char* l1, int y, t_vars* vars)
{
	int	i;
	int	x;
	
	i = 0;
	x = 0;
	while (l1[i] && l1[i + 1] && vars->map->lock)
	{
		if (l1[i] == '0' && l1[i + 1] == '1')
			vars->map->est++;
		if (l1[i] == '1' && l1[i + 1] == '0')
			vars->map->ouest++;
		x++;
	}
}

int	search_NS(char* l1, char* l2, int y, t_vars* vars)
{
	int	i;
	int	x;
	
	i = 0;
	x = 0;
	while (l1[i] && l2[i] && !vars->map->lock)
	{
		if (l1[i] == '0' && l2[i] == '1')
			vars->map->sud++;
		if (l1[i] == '1' && l2[i] == '0')
			vars->map->nord++;
		x++;
	}
}

int	create_NSEO(t_vars* vars)
{
	t_list* old;
	t_list* new;
	int		y;

	old = vars->map->lines;
	new = vars->map->lines->next;
	vars->map->lock = 0;
	while(old)
	{
		search_EO(old, y, vars);
		if (new)
		{
			search_NS(old, new, y, vars);
			new = new->next;
		}
		old = old->next;
		y++;
	}
}
