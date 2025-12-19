/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:24:07 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 10:49:32 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#define COLOR_WALL 0x16173B
#define COLOR_FLOOR 0x286E26
#define COLOR_PLAYER 0xFA0A0A

void    draw_grid(t_textur *img, int i, int j, int color)
{
	int x;
	int y;

	x = 0;
	while (x < GRID_HIEGHT)
	{
		y = 0;
		while (y < GRID_WIDTH)
		{
			set_pixel_color(img, i + x, j + y, color);
			y++;
		}
		x++;
	}
	// y = 0;
	// while (y < GRID_WIDTH - 1)
	// {
	// 	set_pixel_color(img, i + x, j + y, 0);
	// 	y++;
	// }
	// x = 0;
	// while (x < GRID_HIEGHT)
	// {
	// 	set_pixel_color(img, i + x, j + y, 0);
	// 	x++;
	// }
	// x = GRID_HIEGHT - 1;

}

void    draw_player(t_textur *img, int i, int j, int color)
{
	int	x;
	int	y;

	x = - 4;
	while (x < 4)
	{
		y = - 4;
		while (y < 4)
		{
			set_pixel_color(img, i + x, j + y, color);
			y++;
		}
		x++;
	}
}

void draw_img(t_info *info)
{
	int i;
	int j;

	i = 0;
	while (info->map[i])
	{
		j = 0;
		while(info->map[i][j])
		{
			if (info->map[i][j] == '1')
				draw_grid(&info->img, i * GRID_HIEGHT, j * GRID_WIDTH, COLOR_WALL);
			else
				draw_grid(&info->img, i * GRID_HIEGHT, j * GRID_WIDTH, COLOR_FLOOR);
			j++;
		}
		i++;
	}
	draw_player(&info->img, info->player.y_pos , info->player.x_pos, COLOR_PLAYER);
}