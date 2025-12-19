
#include "../../include/cub3D.h"

void	init_step_and_side_dist(t_map *map, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (map->player.x_pos - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - map->player.x_pos)
			* dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (map->player.y_pos - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - map->player.y_pos)
			* dda->delta_dist_y;
	}
}

void	init_dda(t_map *map, t_dda *dda)
{
	dda->map_x = (int)map->player.x_pos;
	dda->map_y = (int)map->player.y_pos;
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
	init_step_and_side_dist(map, dda);
}

void	clear_image(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->screen_height)
	{
		x = 0;
		while (x < map->screen_width)
		{
			put_pixel(map, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
