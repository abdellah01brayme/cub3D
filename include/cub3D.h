/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:34:56 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/20 11:28:07 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>


typedef enum s_num
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	CEIL,
	FLOOR,
	MAP,
	NEW_LINE,
	INVALIDE
}	t_num;

typedef struct s_render
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		ceiling_color;
	int		floor_color;
	int		tex_x;
	double	step;
	double	tex_pos;
}			t_render;

typedef struct s_dda
{
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_dda;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
	double	dir_angle;
	int		fov;
}			t_player;

typedef struct s_textur
{
	void	*img;
	char	*addr;
	int		textur_width;
	int		textur_height;
	int		bits_per_pxl;
	int		length_line;
	int		endian;
}			t_textur;

typedef struct s_map
{
	void		*mlx;
	void		*win;
	char		**map;
	t_player	player;
	t_textur	img;
	t_textur	textures[4];
	int			color_floor;
	int			color_ceil;
	int			screen_width;
	int			screen_height;
}				t_map;

void	render_column_textured(int x, t_map *map, t_dda *dda, t_textur *tex);
int		creat_window(t_map *map);
int		raycasting_loop(t_map *map);
int	calcul_position_texture(t_dda *dda, t_map *map, t_textur *tex);
int	select_texture(t_dda *dda);
void	clear_image(t_map *map);
void	init_dda(t_map *map, t_dda *dda);
int	calcul_position_texture(t_dda *dda, t_map *map, t_textur *tex);
int	select_texture(t_dda *dda);
int	handle_key(int key, t_map *map);
void	put_pixel(t_map *map, int x, int y, int color);
void	cleanup_and_exit(t_map *map);


int		parser(t_map *info, char *file);
int		print_error(char *msg1);
int		print_error2(char *msg1, char *msg2);
int		print_error3(char *msg1, char *file, char *end);
int		check_map(char **map);
int		parse_map(t_map *info, char *file, size_t *offset);
char	*read_file(char *map_path);
void	free_map(char **map);
void	destroy_info(t_map *info);
int		parse_element(t_map *info, char *file, size_t *offset, int type);
int		parse_element(t_map *info, char *file, size_t *offset, int type);
int		initial_info(t_map *info);
int		initial_other(t_map *info);


int		len_map(char **map);
int		handle_key(int key, t_map *info);
void	skip_space(char *str, size_t *offset);
#endif