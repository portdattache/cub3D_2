/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:50:57 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/30 19:19:30 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*tmp;
	void	*content;

	dest = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		content = f(lst -> content);
		tmp = ft_lstnew(content);
		if (!tmp)
		{
			if (content)
				del(content);
			ft_lstclear(&dest, del);
			return (NULL);
		}
		ft_lstadd_back(&dest, tmp);
		lst = lst -> next;
	}
	return (dest);
}
