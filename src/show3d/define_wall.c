/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:18:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/29 16:20:49 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int  check_dir(int i1, int i2, int c)
{
    if (c == 0)
    {
        if (i1 > i2)
            return (2);
        else
            return (4);
    }
    else
    {
        if (i1 > i2)
            return (3);
        else
            return (1);
    }
}

int	define_wall(t_vars **vars, int i)
{
    if ((int)(*vars)->pers->rays[0]->points[i].x % 32 == 0
        || (int)((*vars)->pers->rays[0]->points[i].x + 1) % 32 == 0)
        //&& (int)(*vars)->pers->rays[0]->points[i].y % 32 != 0)
        return (check_dir((*vars)->pers->rays[0]->points[i].x, (*vars)->pers->x, 0));
    else if ((int)(*vars)->pers->rays[0]->points[i].y % 32 == 0
        || (int)((*vars)->pers->rays[0]->points[i].y + 1) % 32 == 0)
        //&& (int)(*vars)->pers->rays[0]->points[i].x % 32 != 0)
        return (check_dir((*vars)->pers->rays[0]->points[i].y, (*vars)->pers->y, 1));
    return (0);
}
