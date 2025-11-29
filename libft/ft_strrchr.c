/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:49:35 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 22:43:42 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*chain;
	size_t	i;

	i = 0;
	chain = 0;
	while (str[i])
	{
		if (str[i] == c)
			chain = (char *)str + i;
		i++;
	}
	if (c == '\0')
		chain = (char *)&str[i];
	return (chain);
}
