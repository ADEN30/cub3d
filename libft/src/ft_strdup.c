/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:56:41 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/25 06:58:55 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = ft_strlen(s1);
	s2 = ft_calloc(i + 1, sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, i + 1);
	return (s2);
}
