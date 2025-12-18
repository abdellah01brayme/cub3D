/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:35:47 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/15 12:15:45 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	set_pixel_color(t_img *img, int y, int x, int color)
{
	char	*pixel;

	pixel = img->addr + y * img->line_length + x * img->byts_per_pixel;
	*((int *)pixel) = color;
}

// int	draw_ray(t_info *info, t_ray *ray)
// {
// 	double	y;
// 	double	x;
// 	double	len;

// 	if (ray->v_dist < ray->h_dist)
// 		len = ray->v_dist;
// 	else
// 		len = ray->h_dist;
// 	x = ray->x_pos;
// 	y = ray->y_pos;
// 	while (1)
// 	{
// 		x += cos(ray->angle);
// 		y += sin(ray->angle);
// 		if (fmod(x, 1) > 0.5) x = x / 1;
// 		if (fmod(y, 1) > 0.5) y = y / 1;
// 		if (sqrt(pow(x - ray->x_pos, 2) + pow(y - ray->y_pos, 2)) > len)
// 		{
// 			return (1);
// 		}
// 		set_pixel_color(&info->img, y, x, 0xFAF20A);
// 	}
// 	return (0);
// }

// int	drawa(t_info *info)
// {
// 	double	max_angle;
// 	double	up_angle;

// 	double	len;
// 	double	wall_hieght;
// 	max_angle = info->player.angle + (PI / 6);
// 	up_angle = (FOV / WIN_WIDTH);
// 	draw_img(info);
// 	init_ray(&info->ray, info, max_angle - PI / 3, 1);
// 	while (info->ray.angle <= max_angle)
// 	{
// 		if (info->ray.h_dist < info->ray.v_dist)
// 			len = info->ray.h_dist;
// 		else
// 			len = info->ray.v_dist;
// 		wall_hieght = (1 / len) * WIN_WIDTH;
// 		if (fmod(wall_hieght, 1) > 0.5) wall_hieght += 1.5;
// 		// printf("%f  %f\n", wall_hieght, len);
// 		draw_ray(info, &info->ray);
// 		info->ray.angle += 4 * up_angle;
// 		init_ray(&info->ray, info, info->ray.angle + up_angle, 1);
// 	}
// 	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
// 	return 0;
// }

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
	t_img img;

	x_txt = info->ray.h_dist % GRID_HIEGHT;printf("====%d\n", x_txt);
	y_txt = 0;
	double step = (double)(*start - end) / 60;
	index_txt = face(info);
	img.addr = mlx_get_data_addr(info->wall_imgs[index_txt], &img.bits_per_pixel,
		&img.line_length, &img.endian);	
	img.byts_per_pixel = img.bits_per_pixel / 8;
	int d = *start;
	while (*start < end)
	{
		y_txt = (*start -d ) / step;
		if (y_txt < 60)
			color = (int)*(img.addr + y_txt * img.line_length + img.byts_per_pixel * x_txt); 
		set_pixel_color(&info->img, *start, x, color);
		if (y_txt > 60) y_txt = 0;
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
	info->win = mlx_new_window(info->mlx, WIN_WIDTH, WIN_HIEGHT, "cub3D");
	mlx_hook(info->win, 2, 1, handle_key, info);
	info->img.img = mlx_new_image(info->mlx,  WIN_WIDTH, WIN_HIEGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel,
		&info->img.line_length, &info->img.endian);	
	info->img.byts_per_pixel = info->img.bits_per_pixel / 8;
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