/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:17:21 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 17:29:55 by aid-bray         ###   ########.fr       */
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

void	destroy_info(t_map *info)
{
	free_map(info->map);
	if (info->textures[NORTH].img)
		mlx_destroy_image(info->mlx, info->textures[NORTH].img);
	if (info->textures[SOUTH].img)
		mlx_destroy_image(info->mlx, info->textures[SOUTH].img);
	if (info->textures[WEST].img)
		mlx_destroy_image(info->mlx, info->textures[WEST].img);
	if (info->textures[EAST].img)
		mlx_destroy_image(info->mlx, info->textures[EAST].img);
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
}
