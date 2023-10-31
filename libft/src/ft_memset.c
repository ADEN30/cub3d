/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:54:44 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/11 11:54:46 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*ptr;

	ptr = b;
	while (len)
	{
		*ptr = (unsigned char)c;
		len--;
		ptr++;
	}
	return (b);
}
