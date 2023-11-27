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

void	stock_EO(char* l1, int y, t_vars* vars)
{
	int	i;
	t_point*	est;
	t_point*	oest;
	
	est = vars->map->E;
	oest = vars->map->O;
	i = 0;
	while (l1[i] && l1[i + 1])
	{
		if (l1[i] == '0' && l1[i + 1] == '1' && --vars->map->est > -1)
		{
			est[vars->map->est].x = i * vars->style->images->wall_image->width;
			est[vars->map->est].y = y * vars->style->images->wall_image->height;
		}
		if (l1[i] == '1' && l1[i + 1] == '0' && --vars->map->ouest > -1)
		{
			oest[vars->map->ouest].x = i * vars->style->images->wall_image->width;
			oest[vars->map->ouest].y = y * vars->style->images->wall_image->height;
		}
		i++;
	}
	vars->map->E = est;
	vars->map->O = oest;
}

void	search_EO(char* l1, t_vars* vars)
{
	int	i;
	
	i = 0;
	while (l1[i] && l1[i + 1])
	{
		if (l1[i] == '0' && l1[i + 1] == '1')
			vars->map->est++;
		if (l1[i] == '1' && l1[i + 1] == '0')
			vars->map->ouest++;
		i++;
	}

}

void	stock_NS(char* l1, char* l2, int y, t_vars* vars)
{
	int	i;
	t_point*	nord;
	t_point*	sud;
	
	nord = vars->map->N;
	sud = vars->map->S;
	i = 0;
	while (l1[i] && l2[i])
	{
		if (l1[i] == '0' && l2[i] == '1' && --vars->map->sud > -1)
			{
			sud[vars->map->sud].x = i * vars->style->images->wall_image->width;
			sud[vars->map->sud].y = y * vars->style->images->wall_image->height;
		}
		if (l1[i] == '1' && l1[i] == '0' && --vars->map->nord > -1)
		{
			nord[vars->map->nord].x = i * vars->style->images->wall_image->width;
			nord[vars->map->nord].y = y * vars->style->images->wall_image->height;
		}
		i++;
	}
	vars->map->S = sud;
	vars->map->N = nord;
}

void	search_NS(char* l1, char* l2, t_vars* vars)
{
	int	i;
	
	i = 0;
	while (l1[i] && l2[i])
	{
		if (l1[i] == '0' && l2[i] == '1')
			vars->map->sud++;
		if (l1[i] == '1' && l2[i] == '0')
			vars->map->nord++;
		i++;
	}
}

void	init_tab(t_vars* vars)
{
	vars->map->E = malloc(sizeof(t_point) * vars->map->est + 1);
	vars->map->O = malloc(sizeof(t_point) * vars->map->ouest + 1);
	vars->map->N = malloc(sizeof(t_point) * vars->map->nord + 1);
	vars->map->S = malloc(sizeof(t_point) * vars->map->sud + 1);
}

int	stock_NSEO(t_vars* vars)
{
	t_list* old;
	t_list* new;
	int		y;

	init_tab(vars);
	old = vars->map->lines;
	new = vars->map->lines->next;
	y = 0;
	while(old)
	{
		stock_EO(old->content, y, vars);
		if (new)
		{
			stock_NS(old->content, new->content, y, vars);
			new = new->next;
		}
		old = old->next;
		y++;
	}
	return (1);
}

void display_tpoint(t_point* tab, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		printf("x: %f y: %f\n", tab[i].x, tab[i].y);
		i++;
	}
}

int	create_NSEO(t_vars* vars)
{
	t_list* old;
	t_list* new;
	int		y;

	old = vars->map->lines;
	new = vars->map->lines->next;
	y = 0;
	while(old)
	{
		search_EO(old->content, vars);
		if (new)
		{
			search_NS(old->content, new->content, vars);
			new = new->next;
		}
		old = old->next;
		y++;
	}
	vars->map->size_e = vars->map->est;
	vars->map->size_o = vars->map->ouest;
	vars->map->size_n = vars->map->nord;
	vars->map->size_s = vars->map->sud;
	stock_NSEO(vars);
	return (1);
}
