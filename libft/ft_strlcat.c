/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:02:13 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 22:59:41 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(src);
	if (!dst && size == 0)
		return (len_s);
	len_d = ft_strlen(dst);
	i = 0;
	if (size <= len_d)
		return (size + len_s);
	while (src[i] && (len_d + i) < (size - 1))
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}
