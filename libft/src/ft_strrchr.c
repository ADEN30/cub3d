/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:58:45 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/11 11:58:58 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((char)c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (i >= 0)
	{
		if (s[i] - (char)c != 0)
			i--;
		else
			return ((char *)(s + i));
	}
	return (0);
}
