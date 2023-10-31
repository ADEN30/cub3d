/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:02:50 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/15 11:50:23 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	len(int n)
{
	int	i;
	int	nb;

	i = 0;
	nb = n;
	if (n == 0)
		return (1);
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	if (n < 0)
		i = i + 1;
	return (i);
}

static char	fill(char *s, int i, int n)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		while (i-- && i > 0)
		{
			s[i] = (nb % 10) + '0';
			nb = nb / 10;
		}
		s[0] = '-';
	}
	while (i--)
	{
		s[i] = (n % 10) + '0';
		n = n / 10;
	}
	return (*s);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*s;

	i = len(n);
	s = ft_calloc(i + 1, sizeof(char));
	if (s == NULL)
		return (NULL);
	fill(s, i, n);
	return (s);
}
