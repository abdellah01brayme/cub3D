/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:35:47 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/11 14:36:07 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


void	set_pixel_color(t_img *img, int y, int x, int color)
{
	char	*pixel;

	pixel = img->addr + y * img->line_length + x * img->byts_per_pixel;
	*((int *)pixel) = color;
}


void	init_dist(t_dda *dda)
{
	if (cos(dda->angle) < 0)
	{
		dda->x_step = -1;
		dda->h_dist = dda->v_to_v * (fmod(dda->x_pos, GRID_WIDTH) / GRID_WIDTH);
	}
	else
	{
		dda->x_step = 1;
		dda->h_dist = dda->h_to_h * ((GRID_WIDTH - fmod(dda->x_pos, GRID_WIDTH)) / GRID_WIDTH);
	}
	if (sin(dda->angle) > 0)
	{
		dda->y_step = 1;
		dda->v_dist = dda->v_to_v * ((GRID_HIEGHT - fmod(dda->y_pos, 1)) / GRID_HIEGHT);
	}
	else
	{
		dda->y_step = -1;
		dda->v_dist = dda->v_to_v * (fmod(dda->y_pos, 1) / GRID_HIEGHT);
	}
}

void	init_dda(t_dda *dda, t_info *info, double angle)
{
	dda->angle = angle;
	dda->x_pos = info->player.x_pos;
	dda->y_pos = info->player.y_pos;
	dda->h_to_h = (1 / fabs(cos(dda->angle))) * GRID_WIDTH;
	dda->v_to_v = (1 / fabs(sin(dda->angle))) * GRID_HIEGHT;
	init_dist(dda);
	if (dda->v_dist < dda->h_dist)
		dda->hit_wall = VERTICAL;
	else
		dda->hit_wall = HORIZONTAL;
}

int	hit(char **map, t_dda *dda)
{
	int		y;
	int		x;
	double	len;

	if (dda->hit_wall == VERTICAL)
		len = dda->v_dist;
	else
		len = dda->h_dist;
	x = fabs(cos(dda->angle)) * len;
	y = fabs(sin(dda->angle)) * len;
	x /= GRID_WIDTH;
	y /= GRID_HIEGHT;
	if (y >= len_map(map) || x >= (int)ft_strlen(map[y]) || !map[y][x] || map[y][x] == '1' || map[y][x] == ' ')
		return (1);
	return (0);
}

void	calcul_hit_wall(t_info *info, t_dda *dda)
{
	while (!hit(info->map, dda))
	{
		if (dda->v_dist < dda->h_dist)
		{
			dda->v_dist += dda->v_to_v;
			dda->hit_wall = VERTICAL;
		}
		else
		{
			dda->h_dist += dda->h_to_h;
			dda->hit_wall = HORIZONTAL;
		}
	}
}

int	draw_ray(t_info *info, t_dda *dda)
{
	double	y;
	double	x;

	x = dda->x_pos;
	y = dda->y_pos;
	while (1)
	{
		x += dda->x_step * fabs(cos(dda->angle));
		y += dda->y_step * fabs(sin(dda->angle));
		set_pixel_color(&info->img, y, x, 0xFAF20A);
		if ((int)y / GRID_HIEGHT >= len_map(info->map) || (int)x / GRID_HIEGHT >= (int)ft_strlen(info->map[(int)y / GRID_HIEGHT]) 
			|| !info->map[(int)y / GRID_HIEGHT][(int)x / GRID_HIEGHT] || info->map[(int)y / GRID_HIEGHT][(int)x / GRID_HIEGHT] == '1'
			|| info->map[(int)y / GRID_HIEGHT][(int)x / GRID_HIEGHT] == ' ')
			return (1);
		(void)info;
	}
	return (0);
}

void	draw(t_info *info)
{
	t_dda	dda;
	double	max_angle;
	double	up_angle;

	max_angle = info->player.angle + (M_PI / 6);
	up_angle = 0.03;
	draw_img(info);
	init_dda(&dda, info, max_angle - M_PI / 3);
	while (dda.angle <= max_angle)
	{
		// calcul_hit_wall(info, &dda);
		draw_ray(info, &dda);
		init_dda(&dda, info, dda.angle + up_angle);
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int	handle_key(int key, t_info *info)
{
	if (key == 65307)
	{
		printf("good bye\n");
		destroy_info(info);
		exit(0);
	}
	draw(info);
	return (0);
}

int	start_game(t_info *info)
{
	info->win = mlx_new_window(info->mlx, WIN_WIDTH, WIN_HIEGHT, "cub3D");
	mlx_hook(info->win, 2, 1, handle_key, info);
	info->img.img = mlx_new_image(info->mlx,  WIN_WIDTH, WIN_HIEGHT);
	info->img.addr = mlx_get_data_addr(&info->img.img, &info->img.bits_per_pixel,
		&info->img.line_length, &info->img.endian);
	info->img.byts_per_pixel = info->img.bits_per_pixel / 8;
	draw(info);
	mlx_loop(info->mlx);
	return (0);
}


	// a 97
	// w 119
	// d 100
	// s 125














































// YASS2002.com@@@