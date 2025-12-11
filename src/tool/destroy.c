/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:17:21 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/03 17:03:09 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_info(t_info *info)
{
	free_map(info->map);
	if (info->wall_imgs[NORTH])
		mlx_destroy_image(info->mlx, info->wall_imgs[NORTH]);
	if (info->wall_imgs[SOUTH])
		mlx_destroy_image(info->mlx, info->wall_imgs[SOUTH]);
	if (info->wall_imgs[WEST])
		mlx_destroy_image(info->mlx, info->wall_imgs[WEST]);
	if (info->wall_imgs[EAST])
		mlx_destroy_image(info->mlx, info->wall_imgs[EAST]);
	//....
	mlx_destroy_display(info->mlx);
	free(info->mlx);
}
