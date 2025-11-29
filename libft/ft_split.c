/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:29:58 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 22:45:42 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (s[i] && s[i] != c)
		count++;
	while (s[i] && s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

size_t	get_lenght_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**free_split(char **p, size_t i)
{
	while (i--)
		free(p[i]);
	free(p);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	nbr_words;
	size_t	i;
	size_t	start;

	if (!s)
		return (NULL);
	start = 0;
	i = 0;
	nbr_words = count_words(s, c);
	ptr = malloc((nbr_words + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < nbr_words)
	{
		while (s[start] && s[start] == c)
			start++;
		ptr[i] = ft_substr(s, start, get_lenght_word(s + start, c));
		if (!ptr[i])
			return (free_split(ptr, i));
		start += get_lenght_word(s + start, c);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
