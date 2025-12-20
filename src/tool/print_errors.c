/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:19:08 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/20 15:16:29 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	print_error(char *msg1)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg1, 2);
	write (2, "\n", 1);
	return (-1);
}

int	print_error2(char *msg1, char *msg2)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg1, 2);
	write (2, "'", 1);
	ft_putstr_fd(msg2, 2);
	write (2, "'\n", 2);
	return (-1);
}

int	print_error3(char *msg1, char *file, char *end)
{
	int	i;

	i = 0;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg1, 2);
	write (2, "'", 1);
	while (file[i] && !ft_strchr(end, file[i]))
		write (2, &file[i++], 1);
	write (2, "'\n", 2);
	return (-1);
}
