/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:29:48 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/09 11:56:51 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*u_dest;
	const unsigned char	*u_src;
	size_t				i;

	i = 0;
	u_src = (const unsigned char *)src;
	u_dest = (unsigned char *)dest;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		i++;
	}
	return (dest);
}
