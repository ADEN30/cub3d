/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:55:57 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/11 11:55:59 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u;

	u = 0;
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	u = n;
	if (u > 9)
	{
		ft_putnbr_fd((u / 10), fd);
		u = u % 10;
	}
	ft_putchar_fd(u + '0', fd);
}
