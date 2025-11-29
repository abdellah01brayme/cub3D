/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:52 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 12:06:50 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*u_dest;
	const unsigned char	*u_src;
	size_t				i;

	i = 0;
	u_dest = (unsigned char *)dest;
	u_src = (const unsigned char *)src;
	if (u_dest < u_src)
	{
		while (i < n)
		{
			u_dest[i] = u_src[i];
			i++;
		}
	}
	if (u_dest > u_src)
		while (n--)
			u_dest[n] = u_src[n];
	return (dest);
}
