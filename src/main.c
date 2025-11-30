/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:28:34 by aid-bray          #+#    #+#             */
/*   Updated: 2025/11/30 11:32:37 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	init_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->color_ceil = -1;
	info->color_floor = -1;
	info->mlx = mlx_init();
	if (!info->mlx)
		return (print_error2("mlx: ", "failed to connection with X11"));
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	char	*file;

	if (ac != 2)
		return (print_error2("Invalide arguments: ", "./cub3D path_to_file"));
	if (init_info(&info))
		return (1);
	file = read_file(av[1]);
	if (parser(&info, file))
		return (free(file), destroy_info(&info), 1);
	free(file);
	destroy_info(&info);
	return (0);
}
