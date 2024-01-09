/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:43:17 by jmathieu          #+#    #+#             */
/*   Updated: 2024/01/07 16:02:16 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	print_error(char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	return (1);
}
