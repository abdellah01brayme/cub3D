
#include "../../include/cub3D.h"


int	select_texture(t_dda *dda)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			return (WEST);
		else if (dda->ray_dir_x < 0)
			return (EAST);
	}
	else
	{
		if (dda->ray_dir_y > 0)
			return (SOUTH);
		else if (dda->ray_dir_y < 0)
			return (NORTH);
	}
	return (-1);
}

int	calcul_position_texture(t_dda *dda, t_map *map, t_textur *tex)
{
	double	wall_x;
	int		tex_x;

	if (dda->side == 0)
		wall_x = map->player.y_pos + dda->perp_wall_dist * dda->ray_dir_y;
	else
		wall_x = map->player.x_pos + dda->perp_wall_dist * dda->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->length_line);
	if (dda->side == 0 && dda->ray_dir_x > 0)
		tex_x = tex->length_line - tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		tex_x = tex->length_line - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->length_line)
		tex_x = tex->length_line - 1;
	return (tex_x);
}
