/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:05:07 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/09 10:00:28 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*my_lst;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	my_lst = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&my_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&my_lst, temp);
		lst = lst->next;
	}
	return (my_lst);
}
