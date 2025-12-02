/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:35:47 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/02 17:16:18 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#define WIN_WIDTH 200
#define WIN_HIEGHT 200

int	handle_key(int key, t_info *info)
{
	if (key == 65307)
	{
		printf("good bye\n");
		destroy_info(info);
		exit(0);
	}

	// a 97
	// w 119
	// d 100
	// s 125
}

void	set_params(int *len, int *max_line, t_info *info)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	*max_line = 0;// ft_strlen(info->map[0]);
	while (info->map[i])
	{
		tmp = ft_strlen(info->map[i]);
		if (tmp > *max_line)
			*max_line = tmp;
		j = 0;
		while (!info->player.x_position && info->map[i][j])
		{
			if (ft_strchr("NSWE", info->map[i][j]))
			{
				info->player.x_position = j;
				info->player.y_position = i;
			}
			j++;
		}
		i++;
	}
	*len = i;
}

void	set_pixel_color(t_params_img *param, int x, int y, int color)
{
	char	*pixel;

	pixel = param->addr + x * param->line_length + y * param->byts_per_pexel;
	*((int *)pixel) = color;
}
int	fill_rectangle(t_params_img *param, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			set_pixel_color(param, i + x * 20, j + y * 20, color);
			j++;
		}
		i++;
	}
}
int	draw(t_info *info, int max_lin, int size_map)
{
	int				i;
	int				j;
	int				color;
	t_params_img	param;

	param.addr = mlx_get_data_addr(info->img, &param.bits_per_pixel, &param.line_length, &param.endian);
	param.byts_per_pexel = param.bits_per_pixel / 8;
	i = 0;
	while (i < size_map)
	{
		j = 0;
		while (j < max_lin)
		{
			if ((j < ft_strlen(info->map[i]) && (info->map[i][j] == '1' || info->map[i][j] == ' ')) || j >= ft_strlen(info->map[i]))
				fill_rectangle(&param, i, j, 0xfff000);
			else if ((j < ft_strlen(info->map[i]) && info->map[i][j] == '0') || j >= ft_strlen(info->map[i]))
				fill_rectangle(&param, i, j, 0x000fff);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}
int	start_game(t_info *info)
{
	int		size_map, max_line;
	int i = 0;
	info->win = mlx_new_window(info->mlx, WIN_WIDTH, WIN_HIEGHT, "cub3D");
	mlx_hook(info->win, 2, 1, handle_key, info);
	set_params(&size_map, &max_line, info);
	info->img = mlx_new_image(info->mlx,  WIN_WIDTH, WIN_HIEGHT);
	draw(info, max_line, size_map);
	mlx_loop(info->mlx);
	return (0);
}
