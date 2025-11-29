/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:28:34 by aid-bray          #+#    #+#             */
/*   Updated: 2025/11/29 16:55:30 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"

void print_info(t_info *info);

int	init_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->color_ceil = -1;
	info->color_floor = -1;
	info->mlx = mlx_init();
	if (!info->mlx)
		return (print_error2("mlx: ", "failed create connection with X11"));
	return (0);
}

int main(int ac, char **av)
{
	t_info	info;
	char	*file;

	if (!av[1])
		return (1);
	
	file = read_file(av[1]);
	if (init_info(&info))
		return (free(file), 1);
	if (parser(&info, file))
		return (free(file), free(info.mlx), 1);
	print_info(&info);
	free(file);
	return (ac && 0);
}
