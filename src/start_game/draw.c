// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   draw.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/12/13 17:36:00 by aid-bray          #+#    #+#             */
// /*   Updated: 2025/12/14 17:14:51 by aid-bray         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/cub3D.h"
// #define COLOR_CEIL 0x16173B
// #define COLOR_FLOOR 0x286E26
// #define WALL_HIEGHT (WIN_HIEGHT / 2)
// // {
// // 	t_ray	ray;
// // 	double	max_angle;
// // 	double	up_angle;

// // 	max_angle = info->player.angle + (PI / 6);
// // 	up_angle = (FOV / WIN_WIDTH) * 2;
// // 	draw_img(info);
// // 	init_ray(&ray, info, max_angle - PI / 3);
// // 	while (ray.angle <= max_angle)
// // 	{
// // 		calcul_hit_wall(info, &ray);
// // 		draw_ray(info, &ray);
// // 		init_ray(&ray, info, ray.angle + up_angle);
// // 	}
// // 	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
// // }
// int	draw(t_info *info)
// {
// 	int		wall_start;
// 	int		wall_end;
// 	int		y;
// 	int		x;
// 	double	up_angle;
// 	double	len;
// 	double	wall_hieght;
// 	x = 0;printf("========================================================\n");
// 	up_angle = (FOV / WIN_WIDTH);
// 	init_ray(&info->ray, info, info->player.angle - PI / 6, 0);
// 	while (x < WIN_WIDTH)
// 	{
// 		if (info->ray.h_dist < info->ray.v_dist)
// 			len = info->ray.h_dist;
// 		else
// 			len = info->ray.v_dist;
// 		printf("%f  ", len);
// 		wall_hieght = GRID_WIDTH * WIN_HIEGHT / len;
// 		printf("%f  \n", wall_hieght);
// 		wall_start = WIN_HIEGHT / 2 - wall_hieght / 2;
// 		wall_end = WIN_HIEGHT / 2 + wall_hieght / 2;
// 		if (wall_start < 0)
// 			wall_start = 0;
// 		if (wall_end >= WIN_HIEGHT)
// 			wall_end = WIN_HIEGHT;
// 		y = 0;
// 		while (y < wall_start)
// 		{
// 			set_pixel_color(&info->img, y, x, COLOR_CEIL);
// 			y++;
// 		}
// 		while (y < wall_end)
// 		{
// 			set_pixel_color(&info->img, y, x, 0x731907);
// 			y++;
// 		}
// 		while (y < WIN_HIEGHT)
// 		{
// 			set_pixel_color(&info->img, y, x, COLOR_FLOOR);
// 			y++;
// 		}
// 		init_ray(&info->ray, info, info->ray.angle + up_angle, x);
// 		x++;
// 	}
// 	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
// 	return (0);
// }