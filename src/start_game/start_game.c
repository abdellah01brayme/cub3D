/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:35:47 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 11:00:52 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	set_pixel_color(t_textur *img, int y, int x, int color)
{
	char	*pixel;

	pixel = img->addr + y * img->length_line + x * img->bits_per_pxl / 8;
	*((int *)pixel) = color;
}

void	calcul_dist(t_info *info)
{
	t_ray	*ray;

	ray = &info->ray;
	while (1)
	{
		if (info->map[(ray->y_pos + ray->v_dist * ray->y_step) / GRID_HIEGHT]
					 [(ray->x_pos + ray->h_dist * ray->x_step) / GRID_HIEGHT] != '0')
			break;
		if (ray->h_dist < ray->v_dist)
		{
			ray->h_dist += GRID_WIDTH;
			ray->hit_wall = HORIZONTAL;
		}
		else
		{
			ray->v_dist += GRID_HIEGHT;
			ray->hit_wall = VERTICAL;
		}
	}
}

void	init_raya(t_info *info, double angle)
{
	t_ray	*ray;

	ray = &info->ray;
	ray->angle = angle;
	ray->x_pos = info->player.x_pos;
	ray->y_pos = info->player.y_pos;
	if (cos(ray->angle) > 0)
	{
		ray->h_dist = GRID_WIDTH - (ray->x_pos % GRID_WIDTH);
		ray->x_step = 1;
	}
	else
	{
		ray->h_dist = (ray->x_pos % GRID_WIDTH);
		ray->x_step = -1;
	}
	if (sin(ray->angle) > 0)
	{
		ray->v_dist = GRID_HIEGHT - (ray->y_pos % GRID_HIEGHT);
		ray->y_step = 1;
	}
	else
	{
		ray->v_dist = (ray->y_pos % GRID_HIEGHT);
		ray->y_step = -1;
	}
	calcul_dist(info);
}

#define COLOR_CEIL 0x0FF6FA
#define COLOR_FLOOR 0x286E26
int	face(t_info *info)
{
	if (info->ray.x_step > 0)
	{
		if (info->ray.y_step > 0 && info->ray.hit_wall == HORIZONTAL)
			return (NORTH);
		else if (info->ray.y_step < 0 && info->ray.hit_wall == HORIZONTAL)
			return (SOUTH);
		return (WEST);
	}
	else
	{
		if (info->ray.y_step > 0 && info->ray.hit_wall == HORIZONTAL)
			return (NORTH);
		else if (info->ray.y_step < 0 && info->ray.hit_wall == HORIZONTAL)
			return (SOUTH);
		return (EAST);
	}
	return (0);
}
void	fill_wall(t_info *info, int *start, int end, int x)
{
	int	index_txt;
	int	x_txt;
	int	y_txt;
	int	color;
	t_textur *img;

	x_txt = info->ray.h_dist % GRID_HIEGHT;printf("====%d\n", x_txt);
	y_txt = 0;
	double step = (double)(*start - end) / 60;
	index_txt = face(info);
	img = &info->textures[index_txt];	
	int d = *start;
	while (*start < end)
	{
		y_txt = fabs((*start -d) / step);

		printf("%d %d  %p\n", y_txt, x_txt, img->addr + y_txt * img->length_line + (img->bits_per_pxl / 8) * x_txt);
		if (y_txt < 64)
			color = (int)*(img->addr + y_txt * img->length_line + (img->bits_per_pxl / 8) * x_txt); 
		set_pixel_color(&info->img, *start, x, color);
		// if (y_txt > 63) y_txt = 0;
		(*start)++;
	}
}
void	draw_ray(t_info *info, int x)
{
	int	wall_hieght;
	int	len;
	int	start_wall;
	int	end_wall;

	if (info->ray.hit_wall == HORIZONTAL)
		len = info->ray.h_dist;
	else
		len = info->ray.v_dist;
	if (len < 1)
		len = 1;
	
	// wall_hieght = (GRID_HIEGHT) * 100 / 60;
	wall_hieght = WIN_WIDTH * 20 / len;
	start_wall = (WIN_HIEGHT / 2) - wall_hieght / 2;
	end_wall = (WIN_HIEGHT / 2) + wall_hieght / 2;
	if (start_wall < 0)
		start_wall = 0;
	if (end_wall > WIN_HIEGHT)
		end_wall = WIN_HIEGHT;
	int	y;
	y = 0;
	while (y < start_wall)
	{
		set_pixel_color(&info->img, y, x, COLOR_CEIL);
		y++;
	}
	// while (y < end_wall)
	// {
	// 	// printf("%d=====\n", y);
	// 	set_pixel_color(&info->img, y, x, 0xDB3A0F);
	// 	y++;
	// }
	fill_wall(info, &y, end_wall, x);
	while (y < WIN_HIEGHT)
	{
		// printf("%d=====\n", y);
		set_pixel_color(&info->img, y, x, COLOR_FLOOR);
		y++;
	}
}

int	drawa(t_info *info)
{
	double	ray_angle_up;
	int		x;

	x = 0;
	ray_angle_up = (PI / 3) / WIN_WIDTH;
	init_raya(info, info->player.angle - PI / 6);
	while (x < WIN_WIDTH)
	{
		draw_ray(info, x);
		// draw_img(info);
		init_raya(info, info->ray.angle + ray_angle_up);
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	return (0);
}

int	handle_key(int key, t_info *info)
{
	double	x,y;
	if (key == 65307)
	{
		printf("good bye\n");
		destroy_info(info);
		exit(0);
	}
	else if (key == 97)// a
	{
		info->player.angle -= ANGLE_UP;
	}
	else if (key == 119)//w
	{
		x = info->player.x_pos + STEP * cos(info->player.angle);
		y = info->player.y_pos + STEP * sin(info->player.angle);
	}
	else if (key == 100)//d
	{
		info->player.angle += ANGLE_UP;
	}
	else if (key == 115)//s
	{
		x = info->player.x_pos - STEP * cos(info->player.angle);
		y = info->player.y_pos - STEP * sin(info->player.angle);
	}
	if (key == 115 || key == 119)
	{
		if (y / GRID_HIEGHT < len_map(info->map) && x / GRID_WIDTH < ft_strlen(info->map[(int)y/ GRID_HIEGHT]) 
			&& info->map[(int)y / GRID_HIEGHT][(int)x / GRID_WIDTH] == '0')
		{
			info->player.x_pos = x;
			info->player.y_pos = y;
		}
	}
	drawa(info);
	return (0);
}

int	start_game(t_info *info)
{
	drawa(info);
	handle_key(0, info);
	mlx_loop(info->mlx);
	return (0);
}


	// a 97
	// w 119
	// d 100
	// s 125














































// YASS2002.com@@@