/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:25:44 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/22 13:51:43 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstclear2(t_list *elem, void (*del)(void *))
{
	ft_lstclear(&elem, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	elem = NULL;
	while (lst)
	{
		temp = f(lst->content);
		if (temp == 0)
			return (ft_lstclear2(elem, del));
		new = ft_lstnew(temp);
		if (!new)
		{
			free(temp);
			return (ft_lstclear2(elem, del));
		}
		ft_lstadd_back(&elem, new);
		lst = lst->next;
	}
	return (elem);
}
