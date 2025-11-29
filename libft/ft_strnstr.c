/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:28:40 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/09 20:21:11 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *littel, size_t len)
{
	size_t	i;
	size_t	len_littel;

	if (*littel == '\0')
		return ((char *)big);
	if (!big)
		return (NULL);
	i = 0;
	len_littel = ft_strlen(littel);
	while (big[i] && (len_littel + i) <= len)
	{
		if (ft_strncmp(big + i, littel, len_littel) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
