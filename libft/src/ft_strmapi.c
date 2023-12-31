/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:57:50 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/22 11:48:02 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptrf;

	i = 0;
	if (!s)
		return (NULL);
	if (f != 0)
	{
		ptrf = ft_calloc((ft_strlen(s) + 1), sizeof(char));
		if (ptrf == NULL)
			return (NULL);
		while (s[i])
		{
			ptrf[i] = f(i, *(s + i));
			i++;
		}
		return (ptrf);
	}
	return (ft_calloc(1, sizeof(char)));
}
