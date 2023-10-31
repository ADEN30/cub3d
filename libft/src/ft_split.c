/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:49:30 by jmathieu          #+#    #+#             */
/*   Updated: 2023/01/24 16:19:22 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			words++;
		}
	}
	return (words);
}

static int	ft_lenword(char const *s, int j, char c)
{
	int	len;

	len = 0;
	while (s[j] && s[j] != c)
	{
		len++;
		j++;
	}
	return (len);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
	{
		if (str[i])
			free((char *)str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

static char	*ft_cpy(char const *s, int j, int len)
{
	char	*stri;
	int		i;

	i = 0;
	stri = ft_calloc((len + 1), sizeof(char));
	if (stri == 0)
		return (NULL);
	while (i < len && s[j])
	{
		stri[i] = s[j];
		i++;
		j++;
	}
	return (stri);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = ft_count(s, c);
	str = ft_calloc((words + 1), sizeof(*str));
	if (str == 0)
		return (NULL);
	while (i < words)
	{
		while (s[j] == c && s[j])
			j++;
		str[i] = ft_cpy(s, j, ft_lenword(s, j, c));
		if (str[i] == 0)
			return (ft_free(str, i));
		i++;
		j = j + ft_lenword(s, j, c);
	}
	return (str);
}
