/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:37:56 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 22:44:03 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen_trim(const char *s, const char *set)
{
	size_t	start;
	size_t	stop;

	start = 0;
	while (in_set(s[start], set))
		start++;
	stop = start;
	if (s[stop] == '\0')
		return (0);
	while (s[stop])
		stop++;
	stop--;
	while (in_set(s[stop], set))
		stop--;
	return (stop - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen_trim(s1, set);
	ptr = (char *)malloc (len + 1);
	if (!ptr)
		return (NULL);
	while (in_set(s1[i], set))
		i++;
	while (j < len)
	{
		ptr[j] = s1[i + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
