/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:01:53 by aid-bray          #+#    #+#             */
/*   Updated: 2024/10/25 18:00:34 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_lenght(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*get_array(unsigned int n, int len, char sign)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = len - 1;
	ptr[0] = '0';
	while (n)
	{
		ptr[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	if (sign == '-')
		ptr[i] = '-';
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	unsigned int	u_n;
	int				len;
	char			sign;

	sign = '\0';
	len = 0;
	if (n < 0)
	{
		sign = '-';
		u_n = -n;
		len++;
	}
	else
		u_n = (unsigned int)n;
	len += get_lenght(u_n);
	return (get_array(u_n, len, sign));
}
