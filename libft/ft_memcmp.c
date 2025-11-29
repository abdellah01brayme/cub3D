/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:12:31 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/06 11:18:10 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;
	size_t				i;

	i = 0;
	u_s1 = (const unsigned char *)s1;
	u_s2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (u_s1[i] == u_s2[i] && i < (n - 1))
		i++;
	return (u_s1[i] - u_s2[i]);
}
