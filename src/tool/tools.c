/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:03:50 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 15:40:49 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	initial_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->color_ceil = -1;
	info->color_floor = -1;
	info->mlx = mlx_init();
	if (!info->mlx)
	{
		print_error2("mlx: ", "failed to connection with X11");
		exit(1);
	}
	return (0);
}

int	initial_other(t_info *info)
{
	info->win = mlx_new_window(info->mlx, WIN_WIDTH, WIN_HIEGHT, "cub3D");
	if (!info->win)
		return (print_error("open window failed"));
	mlx_hook(info->win, 2, 1L << 0, handle_key, info);
	// mlx_hook(info->win, 17, 0, close_wind, info);
	info->img.img = mlx_new_image(info->mlx,  WIN_WIDTH, WIN_HIEGHT);
	if (!info->win)
		return (print_error("Create image failed"));
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pxl,
		&info->img.length_line, &info->img.endian);
	return (0);
}

void	skip_space(char *str, size_t *offset)
{
	while (str[*offset] == ' ')
		(*offset)++;
}