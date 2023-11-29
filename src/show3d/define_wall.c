/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:18:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/11/29 15:55:28 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	define_wall(t_vars **vars, int i)
{
    if (((int)(*vars)->pers->rays[0]->points[i].x % 32 == 0
        || (int)((*vars)->pers->rays[0]->points[i].x + 1) % 32 == 0)
        && (int)(*vars)->pers->rays[0]->points[i].y % 32 != 0)
        return (2);
    else if (((int)(*vars)->pers->rays[0]->points[i].y % 32 == 0
        || (int)((*vars)->pers->rays[0]->points[i].y + 1) % 32 == 0)
        && (int)(*vars)->pers->rays[0]->points[i].x % 32 != 0)
        return (1);
    else if (((int)(*vars)->pers->rays[0]->points[i].y % 32 == 0
        || (int)((*vars)->pers->rays[0]->points[i].y + 1) % 32 == 0)
        && ((int)(*vars)->pers->rays[0]->points[i].x % 32 == 0
        || (int)((*vars)->pers->rays[0]->points[i].x + 1) % 32 == 0))
        return (0);
    else
        return (3);
    return (0);
}
