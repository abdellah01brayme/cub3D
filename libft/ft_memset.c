/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:56:23 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/09 11:24:18 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*u_s;
	unsigned char	u_c;
	size_t			i;

	i = 0;
	u_c = (unsigned char)c;
	u_s = (unsigned char *)s;
	while (i < n)
	{
		u_s[i] = u_c;
		i++;
	}
	return (s);
}
