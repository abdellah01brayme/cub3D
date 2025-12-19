
#include "../../include/cub3D.h"

void	move_forward_backward(t_map *map, double speed)
{
	double	new_x;
	double	new_y;

	new_x = map->player.x_pos + cos(map->player.dir_angle) * speed;
	new_y = map->player.y_pos + sin(map->player.dir_angle) * speed;
	if (map->map[(int)map->player.y_pos][(int)new_x] != '1')
		map->player.x_pos = new_x;
	if (map->map[(int)new_y][(int)map->player.x_pos] != '1')
		map->player.y_pos = new_y;
}

void	strafe(t_map *map, double speed)
{
	double	perp_dir_y;
	double	new_x;
	double	new_y;
	double	perp_dir_x;

	perp_dir_x = -sin(map->player.dir_angle);
	perp_dir_y = cos(map->player.dir_angle);
	new_x = map->player.x_pos + perp_dir_x * speed;
	new_y = map->player.y_pos + perp_dir_y * speed;
	if (map->map[(int)new_y][(int)new_x] != '1')
	{
		map->player.x_pos = new_x;
		map->player.y_pos = new_y;
	}
}

void	rotate_player(t_map *map, double angle)
{
	map->player.dir_angle += angle;
	if (map->player.dir_angle < 0)
		map->player.dir_angle += 2 * M_PI;
	if (map->player.dir_angle >= 2 * M_PI)
		map->player.dir_angle -= 2 * M_PI;
}

void	put_pixel(t_map *map, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= map->screen_width || y >= map->screen_height)
		return ;
	dst = map->img.addr + (y * map->img.length_line + x
			* (map->img.bits_per_pxl / 8));
	*(unsigned int *)dst = color;
}

int	handle_key(int key, t_map *map)
{
	double	speed;
	double	rot_speed;

	speed = 0.15;
	rot_speed = 0.1;
	if (key == 65307)
		cleanup_and_exit(map);
	if (key == 65361)
		rotate_player(map, -rot_speed);
	if (key == 65363)
		rotate_player(map, rot_speed);
	if (key == 119)
		move_forward_backward(map, speed);
	if (key == 115)
		move_forward_backward(map, -speed);
	if (key == 97)
		strafe(map, speed);
	if (key == 100)
		strafe(map, -speed);
	clear_image(map);
	raycasting_loop(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	return (0);
}
