/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:41:04 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 12:00:34 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*u_str;
	unsigned char		u_c;
	size_t				i;

	i = 0;
	u_c = (unsigned char)c;
	u_str = (const unsigned char *)s;
	while (i < n)
	{
		if (u_str[i] == u_c)
			return ((void *)u_str + i);
		i++;
	}
	return (NULL);
}
