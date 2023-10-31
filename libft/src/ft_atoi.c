/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:47:18 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/11 11:47:23 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 1;
	nb = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == 32))
			i++;
	while (str[i] && (str[i] == 45 || str[i] == 43))
	{
		if (str[i + 1] && (str[i + 1] < '0' || str[i + 1] > '9'))
			return (0);
		if (str[i] == 45)
			j = -j;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
			nb = nb * 10 + (str[i] - 48);
			i++;
	}
	return (nb *= j);
}
