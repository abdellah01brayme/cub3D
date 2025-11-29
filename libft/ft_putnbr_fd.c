/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:57:06 by aid-bray          #+#    #+#             */
/*   Updated: 2024/11/08 20:28:30 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u_n;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u_n = -n;
	}
	else
		u_n = n;
	if (u_n < 10)
		ft_putchar_fd(u_n + '0', fd);
	else
	{
		ft_putnbr_fd(u_n / 10, fd);
		ft_putchar_fd(u_n % 10 + '0', fd);
	}
}
