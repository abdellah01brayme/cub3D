
#include "../../include/cub3D.h"

int	creat_window(t_map *map)
{
	raycasting_loop(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	mlx_loop(map->mlx);
	return (0);
}
