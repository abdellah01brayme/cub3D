/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:55:09 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/09 12:01:18 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*delete;

	if (!lst || !del)
		return ;
	delete = *lst;
	while (delete)
	{
		temp = delete;
		delete = delete->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
