/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:34:56 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 11:07:05 by aid-bray         ###   ########.fr       */
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

# define VERTICAL 1
# define HORIZONTAL 0
# define WIN_WIDTH 780
# define WIN_HIEGHT 780
# define GRID_WIDTH 60
# define GRID_HIEGHT 60
# define STEP 5
# define ANGLE_UP 0.05
#define PI 3.14159265358979323846
# define FOV (PI / 3)
#include <stdio.h>
typedef enum s_num
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	CEIL,
	FLOOR,
	MAP,
	NEW_LINE
}	t_num;

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	double	angle;
	int		y_step;
	int		x_step;
}			t_player;

typedef struct s_ray
{
	int		index;
	int		x_pos;
	int		y_pos;
	int		h_to_h;
	int		v_to_v;
	int		h_dist;
	int		v_dist;
	int		x_step;
	int		y_step;
	double	angle;
	int		hit_wall;
}			t_ray;

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

typedef struct s_info
{
	void		*mlx;
	void		*win;
	char		**map;
	t_ray		ray;
	t_player	player;
	// void		*wall_imgs[4];
	// int			wall_width[4];
	// int			wall_height[4];
	t_textur	img;
	t_textur	textures[4];
	int			color_floor;
	int			color_ceil;
}				t_info;


int		parser(t_info *info, char *file);
int		print_error(char *msg1);
int		print_error2(char *msg1, char *msg2);
int		print_error3(char *msg1, char *file, char *end);
int		check_map(char **map);
int		parse_map(t_info *info, char *file, size_t *offset);
char	*read_file(char *map_path);
void	free_map(char **map);
void	destroy_info(t_info *info);
int		parse_element(t_info *info, char *file, size_t *offset, int type);
int		parse_element(t_info *info, char *file, size_t *offset, int type);
void	set_pixel_color(t_textur *param, int y, int x, int color);
int		initial_info(t_info *info);
int		initial_other(t_info *info);


int		start_game(t_info *info);
void 	draw_img(t_info *info);
int		len_map(char **map);
int		draw(t_info *info);
void	init_ray(t_ray *ray, t_info *info, double angle, int index);
int		handle_key(int key, t_info *info);
void	skip_space(char *str, size_t *offset);
#endif