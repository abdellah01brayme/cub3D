
#include "../../include/cub3D.h"

static double	calc_ray_angle(t_map *map, int x)
{
	double	screen_ratio;
	double	fov_radians;
	double	angle_offset;
	double	ray_angle;

	screen_ratio = (double)x / map->screen_width;
	fov_radians = map->player.fov * (M_PI / 180);
	angle_offset = (screen_ratio - 0.5) * fov_radians;
	ray_angle = map->player.dir_angle + angle_offset;
	return (ray_angle);
}

static void	find_wall(t_dda *dda, t_map *map)
{
	dda->hit = 0;
	while (!dda->hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map->map[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
	}
}

static double	calc_perp_dist(t_dda *dda)
{
	if (dda->side == 0)
		return (dda->side_dist_x - dda->delta_dist_x);
	return (dda->side_dist_y - dda->delta_dist_y);
}

static double	correct_distance(t_dda *dda, t_map *map)
{
	double	new_dis;
	double	corect;

	corect = map->player.dir_angle - dda->ray_angle;
	new_dis = dda->perp_wall_dist * cos(corect);
	return (new_dis);
}

int	raycasting_loop(t_map *map)
{
	int			x;
	t_dda		dda;
	int			tex_id;
	t_textur	*tex;

	x = 0;
	while (x < map->screen_width)
	{
		dda.ray_angle = calc_ray_angle(map, x);
		dda.ray_dir_x = cos(dda.ray_angle);
		dda.ray_dir_y = sin(dda.ray_angle);
		init_dda(map, &dda);
		find_wall(&dda, map);
		dda.perp_wall_dist = calc_perp_dist(&dda);
		dda.perp_wall_dist = correct_distance(&dda, map);
		if (dda.perp_wall_dist <= 0)
			dda.perp_wall_dist = 0.0001;
		tex_id = select_texture(&dda);
		tex = &map->textures[tex_id];
		render_column_textured(x, map, &dda, tex);
		x++;
	}
	return (0);
}
